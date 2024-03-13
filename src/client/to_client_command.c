#include "to_client_command.h"

Attribute* _to_get_self(TOClient* client) {
    to_send_use_request(client->socket, "self", NULL, 0);

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
    Attribute* self = _to_get_self(client);

    if(self != NULL) {
        to_attribute_stringify(self);
        to_free_attribute(self);
    } else {
        TO_LOG(TO_WARNING, "Failed to get self");
    }
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

    to_send_use_request(client->socket, "vision", NULL, 0);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);

    if(useResponse.type != ATTRIBUTE_RESPONSE)
        return;

    TOAttributeResponse aResponse;
    to_recv_attribute_response(client->socket, &aResponse);

    #define TO_CLIENT_MAP_PREVIEW_WIDTH 50
    #define TO_CLIENT_MAP_PREVIEW_HEIGHT 15

    char map[TO_CLIENT_MAP_PREVIEW_WIDTH][TO_CLIENT_MAP_PREVIEW_HEIGHT];
    memset(map, ' ', sizeof(map));

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

        long long xDelta = (thingXCord - xCord) + (TO_CLIENT_MAP_PREVIEW_WIDTH / 2);
        long long yDelta = (thingYCord - yCord) + (TO_CLIENT_MAP_PREVIEW_HEIGHT / 2);

        if((xDelta >= 0 && xDelta < TO_CLIENT_MAP_PREVIEW_WIDTH) && (yDelta >= 0 && yDelta < TO_CLIENT_MAP_PREVIEW_HEIGHT)) {
            char character = '?';

            if(_to_has_material(entity, "Stone"))
                character = '#';

            if(_to_has_material(entity, "Grass"))
                character = ',';

            if(to_set_find_attribute_name(entity, "Humanoid") != NULL)
                character = 'H';

            if(character == '?')
                to_attribute_stringify(entity);

            map[xDelta][yDelta] = character;
        }

        to_free_attribute(entity);
    }

    map[(TO_CLIENT_MAP_PREVIEW_WIDTH / 2)][(TO_CLIENT_MAP_PREVIEW_HEIGHT / 2)] = 'P';

    printf("Map around (%dx%d):\n", TO_CLIENT_MAP_PREVIEW_WIDTH, TO_CLIENT_MAP_PREVIEW_HEIGHT);

    putc('+', stdout);

    for(int x = 0; x < TO_CLIENT_MAP_PREVIEW_WIDTH; ++x)
        putc('-', stdout);

    printf("+\n");

    for(int y = 0; y < TO_CLIENT_MAP_PREVIEW_HEIGHT; ++y) {
        putc('|', stdout);
        for(int x = 0; x < TO_CLIENT_MAP_PREVIEW_WIDTH; ++x)
            putc(map[x][(TO_CLIENT_MAP_PREVIEW_HEIGHT - 1) - y], stdout);
        printf("|\n");
    }

    putc('+', stdout);

    for(int x = 0; x < TO_CLIENT_MAP_PREVIEW_WIDTH; ++x)
        putc('-', stdout);

    printf("+\n");

    free(aResponse.attributes);
}

void to_client_go_callback(TOClient* client, int argc, char* argv[]) {
    if(argc <= 1)
        return;

    Attribute* self = _to_get_self(client);
    if(self == NULL)
        return;

    MovementUse use;
    if(!_to_get_position(self, &use.xCord, &use.yCord)) {
        to_free_attribute(self);
        return;
    }

    to_free_attribute(self);

    if(strcmp(argv[1], "up") == 0)
        use.yCord += 1;
    else if(strcmp(argv[1], "down") == 0)
        use.yCord -= 1;
    else if(strcmp(argv[1], "left") == 0)
        use.xCord -= 1;
    else if(strcmp(argv[1], "right") == 0)
        use.xCord += 1;

    to_send_use_request(client->socket, "go", &use, sizeof(use));

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);
}

void to_client_ghand_callback(TOClient* client, int argc, char* argv[]) {
    if(argc <= 2)
        return;

    Attribute* self = _to_get_self(client);
    if(self == NULL)
        return;

    GodlyHandUse use;
    memcpy(use.material, argv[2], 16);

    if(!_to_get_position(self, &use.xCord, &use.yCord)) {
        to_free_attribute(self);
        return;
    }

    to_free_attribute(self);

    if(strcmp(argv[1], "up") == 0)
        use.yCord += 1;
    else if(strcmp(argv[1], "down") == 0)
        use.yCord -= 1;
    else if(strcmp(argv[1], "left") == 0)
        use.xCord -= 1;
    else if(strcmp(argv[1], "right") == 0)
        use.xCord += 1;

    to_send_use_request(client->socket, "ghand", &use, sizeof(use));

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);
}
