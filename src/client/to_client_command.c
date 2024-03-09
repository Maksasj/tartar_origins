#include "to_client_command.h"

void _to_send_use_request(TOClient* client, int argc, char* argv[]) {
    char arguments[16][16];
    for(int i = 0; i < 16; ++i)
        memset(arguments[i], '\0', 16);

    for(int i = 0; i < argc; ++i)
        strcpy(arguments[i], argv[i]);

    to_send_use_request(client->socket, arguments, sizeof(arguments));
}

Attribute* _to_get_self(TOClient* client) {
    char *args[] = {"self"};

    _to_send_use_request(client, 1, args);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);

    if(useResponse.type != ATTRIBUTE_RESPONSE)
        return NULL;

    TOAttributeResponse aResponse;
    to_recv_attribute_response(client->socket, &aResponse);

    if(aResponse.count != 1)
        return NULL;

    // Not right
    Attribute* self = aResponse.attributes[0];

    free(aResponse.attributes);

    return self;
}

void to_client_get_self_callback(TOClient* client, int argc, char* argv[]) {
    char *args[] = {"self"};

    _to_send_use_request(client, 1, args);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);

    if(useResponse.type != ATTRIBUTE_RESPONSE)
        return;

    TOAttributeResponse aResponse;
    to_recv_attribute_response(client->socket, &aResponse);

    for (int i = 0; i < aResponse.count; ++i) {
        to_attribute_stringify(aResponse.attributes[i]);
        to_free_attribute(aResponse.attributes[i]);
    }

    free(aResponse.attributes);
}

void to_client_use_callback(TOClient* client, int argc, char* argv[]) {
    _to_send_use_request(client, argc, argv);

    TOUseResponse response;
    to_recv_use_response(client->socket, &response);
}

// Todo fix memory leaks
void to_client_map_callback(TOClient* client, int argc, char* argv[]) {
    Attribute* self = _to_get_self(client);
    if(self == NULL)
        return;

    long long xCord;
    long long yCord;
    if(!_to_get_position(self, &xCord, &yCord))
        return;

    to_free_attribute(self);

    char *args[] = {"vision"};
    _to_send_use_request(client, 1, args);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);

    if(useResponse.type != ATTRIBUTE_RESPONSE)
        return;

    TOAttributeResponse aResponse;
    to_recv_attribute_response(client->socket, &aResponse);

    char map[15][15];
    memset(map, '*', sizeof(map));

    for(int i = 0; i < aResponse.count; ++i) {
        Attribute* entity = aResponse.attributes[i];

        if(entity == NULL)
            continue;

        long long thingXCord;
        long long thingYCord;
        if(!_to_get_position(entity, &thingXCord, &thingYCord)) {
            to_free_attribute(entity);
            continue;
        }

        to_free_attribute(entity);

        long long xDelta = (thingXCord - xCord) + 7;
        long long yDelta = (thingYCord - yCord) + 7;

        if((xDelta >= 0 && xDelta <= 14) && (yDelta >= 0 && yDelta <= 14)) {
            char character = '?';

            if(_to_has_material(entity, "Stone"))
                character = '#';

            if(_to_has_material(entity, "Grass"))
                character = ',';

            if(character == '?')
                to_attribute_stringify(entity);

            map[14 - yDelta][xDelta] = character;
        }
    }

    map[7][7] = 'P';

    printf("Map around (15x15):\n");
    for(int y = 0; y < 15; ++y)
        printf("%.15s\n", map[y]);

    free(aResponse.attributes);
}

void to_client_go_callback(TOClient* client, int argc, char* argv[]) {
    if(argc <= 1)
        return;

    Attribute* self = _to_get_self(client);
    if(self == NULL)
        return;

    long long xCord;
    long long yCord;
    if(!_to_get_position(self, &xCord, &yCord)) {
        to_free_attribute(self);
        return;
    }

    to_free_attribute(self);

    if(strcmp(argv[1], "up") == 0)
        yCord += 1;
    else if(strcmp(argv[1], "down") == 0)
        yCord -= 1;
    else if(strcmp(argv[1], "left") == 0)
        xCord -= 1;
    else if(strcmp(argv[1], "right") == 0)
        xCord += 1;

    unsigned long long size = 3 + 2 * sizeof(long long);
    char* buffer = malloc(size);
    memcpy(buffer, "go", 3);

    memcpy(buffer + 3, &xCord, sizeof(long long));
    memcpy(buffer + 3 + sizeof(long long), &yCord, sizeof(long long));

    to_send_use_request(client->socket, buffer, size);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);
}

void to_client_ghand_callback(TOClient* client, int argc, char* argv[]) {
    if(argc <= 2)
        return;

    Attribute* self = _to_get_self(client);
    if(self == NULL)
        return;

    long long xCord;
    long long yCord;
    if(!_to_get_position(self, &xCord, &yCord)) {
        to_free_attribute(self);
        return;
    }

    to_free_attribute(self);

    if(strcmp(argv[1], "up") == 0)
        yCord += 1;
    else if(strcmp(argv[1], "down") == 0)
        yCord -= 1;
    else if(strcmp(argv[1], "left") == 0)
        xCord -= 1;
    else if(strcmp(argv[1], "right") == 0)
        xCord += 1;

    unsigned long long size = 6 + 16 + 2 * sizeof(long long);
    char* buffer = malloc(size);
    memcpy(buffer, "ghand", 6);
    memcpy(buffer + 6, argv[2], 16);

    memcpy(buffer + 16 + 6, &xCord, sizeof(long long));
    memcpy(buffer + 16 + 6 + sizeof(long long), &yCord, sizeof(long long));

    to_send_use_request(client->socket, buffer, size);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);
}
