#include "to_response_packages.h"

int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response) {
    recv(socket, response, sizeof(TOClientConnectionResponse), 0);

    if((response->info.success != 1) && (response->info.type != TO_CLIENT_CONNECTION_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

void to_send_client_connection_response(int socket, Entity character) {
    TOClientConnectionResponse response;

    response.info.type = TO_CLIENT_CONNECTION_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.character = character;

    send(socket, &response, sizeof(TOClientConnectionResponse), 0);
}





void to_send_entity_response(int socket, Entity* entity) {
    send(socket, entity, sizeof(Entity), 0);

    for(int i = 0; i < entity->attributeCount; ++i)
        send(socket, entity->attributes[i], sizeof(Attribute), 0);
}

Entity* to_recv_entity_response(int socket) {
    Entity* entity = malloc(sizeof(Entity));
    recv(socket, entity, sizeof(Entity), 0);

    for(int i = 0; i < entity->attributeCount; ++i) {
        Attribute* attribute = malloc(sizeof(Attribute));
        recv(socket, attribute, sizeof(Attribute), 0);

        entity->attributes[i] = attribute;
    }

    return entity;
}



/*
int to_recv_character_info_response(int socket, TOCharacterInfoResponse* response) {
    recv(socket, response, sizeof(TOCharacterInfoResponse), 0);

    if((response->info.success != 1) && (response->info.type != TO_CHARACTER_INFO_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

void to_send_character_info_response(int socket, int xPos, int yPos) {
    TOCharacterInfoResponse response;

    response.info.type = TO_CHARACTER_INFO_RESPONSE_PACKAGE;
    response.info.success = 1;

    // response.stats = stats;
    response.xPos = xPos;
    response.yPos = yPos;

    send(socket, &response, sizeof(TOCharacterInfoResponse), 0);
}

int to_recv_tile_info_response(int socket, TOTileInfoResponse* response) {
    recv(socket, response, sizeof(TOTileInfoResponse), 0);

    if((response->info.success != 1) && (response->info.type != TO_TILE_INFO_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

void to_send_tile_info_response(int socket, Tile tile) {
    TOTileInfoResponse response;

    response.info.type = TO_TILE_INFO_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.tile = tile;

    send(socket, &response, sizeof(TOTileInfoResponse), 0);
}

int to_recv_near_creatures_count_response(int socket, TONearCreaturesCountResponse* response) {
    recv(socket, response, sizeof(TONearCreaturesCountResponse), 0);

    if((response->info.success != 1) && (response->info.type != TO_NEAR_CREATURES_COUNT_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

void to_send_near_creatures_response(int socket, unsigned int count) {
    TONearCreaturesCountResponse response;

    response.info.type = TO_NEAR_CREATURES_COUNT_RESPONSE_PACKAGE;
    response.info.success = 1;
    response.count = count;

    send(socket, &response, sizeof(TONearCreaturesCountResponse), 0);
}

int to_recv_creature_info_response(int socket, TOCreatureInfoResponse* response) {
    recv(socket, response, sizeof(TOCreatureInfoResponse), 0);

    if((response->info.success != 1) && (response->info.type != TO_CREATURE_INFO_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

void to_send_creature_info_response(int socket, CreatureInfo info) {
    TOCreatureInfoResponse response;

    response.info.type = TO_CREATURE_INFO_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.creature = info;

    send(socket, &response, sizeof(TOCreatureInfoResponse), 0);
}
*/