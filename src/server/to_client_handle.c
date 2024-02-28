#include "to_client_handle.h"

#include "to_server.h"

TOClientHandle* to_create_client_handle(struct TOServer* server, Connection* connection) {
    TOClientHandle* handle = malloc(sizeof(TOClientHandle));

    handle->server = server;
    handle->connection = connection;

    return handle;
}

void to_handle_client_connection_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    // Todo
}

void to_handle_character_position_update_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    Connection* connection = handle->connection;

    TOCharacterPosUpdateRequest request;
    memcpy(&request, buffer, sizeof(TOCharacterPosUpdateRequest));

    connection->character->xPos = request.newX;
    connection->character->yPos = request.newY;

    printf("TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE %d %d\n", request.newX, request.newY);
}

void to_handle_character_info_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    Connection* connection = handle->connection;

    TOCharacterInfoResponse response;
    response.type = TO_CHARACTER_INFO_RESPONSE_PACKAGE;

    response.stats = connection->character->stats;
    response.xPos = connection->character->xPos;
    response.yPos = connection->character->yPos;

    send(connection->c_socket, &response, sizeof(TOCharacterInfoResponse), 0);

    printf("TO_CHARACTER_INFO_REQUEST_PACKAGE\n");
}

void to_handle_tile_info_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    Connection* connection = handle->connection;
    TOServer* server = handle->server;

    TOTileInfoRequest request;
    memcpy(&request, buffer, sizeof(TOTileInfoRequest));

    TOTileInfoResponse response;
    response.type = TO_TILE_INFO_RESPONSE_PACKAGE;
    response.tile = to_world_get_tile(server->world, request.xPos, request.yPos);

    send(connection->c_socket, &response, sizeof(TOTileInfoResponse), 0);

    printf("TO_TILE_INFO_RESPONSE_PACKAGE\n");
}

void to_near_creatures_count_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    Connection* connection = handle->connection;
    TOServer* server = handle->server;

    TONearCreaturesCountResponse response;

    response.type = TO_NEAR_CREATURES_COUNT_RESPONSE_PACKAGE;
    response.count = 0;

    for(unsigned int i = 0; i < 1024; ++i) {
        if(server->world->creatures[i] != NULL)
            ++response.count;
    }

    response.count += (server->connectionIndex - 1);

    send(connection->c_socket, &response, sizeof(TONearCreaturesCountResponse), 0);

    printf("TO_NEAR_CREATURES_COUNT_REQUEST_PACKAGE\n");
}

void to_near_creatures_info_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    Connection* connection = handle->connection;
    TOServer* server = handle->server;

    unsigned int index = 0;
    Creature creature[1024];

    for(unsigned int i = 0; i < 1024; ++i) {
        if(server->world->creatures[i] == NULL)
            continue;

        creature[index].type = MONSTER_CREATURE;
        creature[index].stats = server->world->creatures[i]->stats;
        creature[index].xPos = server->world->creatures[i]->xPos;
        creature[index].yPos = server->world->creatures[i]->yPos;
        ++index;
    }

    for(unsigned int i = 0; i < server->connectionIndex; ++i) {
        if(server->connections[i] == handle->connection)
            continue;

        creature[index].type = PLAYER_CREATURE;
        creature[index].stats = server->connections[i]->character->stats;
        creature[index].xPos = server->connections[i]->character->xPos;
        creature[index].yPos = server->connections[i]->character->yPos;
        ++index;
    }

    TONearCreaturesInfoRequest request;
    memcpy(&request, buffer, sizeof(TONearCreaturesInfoRequest));

    if(request.index > index) {
        TOCreatureInfoResponse response;
        response.type = TO_CREATURE_INFO_RESPONSE_PACKAGE;
        response.success = 0;
        send(connection->c_socket, &response, sizeof(TOCreatureInfoResponse), 0);
    }

    TOCreatureInfoResponse response;
    response.type = TO_CREATURE_INFO_RESPONSE_PACKAGE;
    response.success = 1;
    response.creature = creature[request.index];
    send(connection->c_socket, &response, sizeof(TOCreatureInfoResponse), 0);

    printf("TO_NEAR_CREATURES_INFO_REQUEST_PACKAGE\n");
}

int to_handle_client(void *ptr) {
    TOClientHandle* handle = (TOClientHandle*) ptr;
    Connection* connection = handle->connection;

    char buffer[1024];
    memset(&buffer, 0, sizeof(buffer));

    TOClientHandlePacketCallback callbacks[] = {
        { TO_CLIENT_CONNECTION_REQUEST_PACKAGE,         NULL },

        { TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE, to_handle_character_position_update_request_packet },
        { TO_CHARACTER_INFO_REQUEST_PACKAGE,            to_handle_character_info_request_packet },

        { TO_TILE_INFO_REQUEST_PACKAGE,                 to_handle_tile_info_request_packet },

        { TO_NEAR_CREATURES_COUNT_REQUEST_PACKAGE,      to_near_creatures_count_request_packet },
        { TO_NEAR_CREATURES_INFO_REQUEST_PACKAGE,       to_near_creatures_info_request_packet }
    };
    unsigned long long callbackCount = sizeof(callbacks) / sizeof(TOClientHandlePacketCallback);

    while(1) {
        int length = recv(connection->c_socket, buffer, sizeof(buffer), 0);

        TOReqPackageType type;
        memcpy(&type, buffer, sizeof(TOReqPackageType));

        for(unsigned int i = 0; i < callbackCount; ++i) {
            if(type == callbacks[i].type) {
                callbacks[i].callback(handle, buffer, length);
                break;
            }
        }
    }

    close(connection->c_socket);

    return 0;
}
