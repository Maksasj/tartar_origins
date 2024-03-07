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

    Attribute* position = to_set_find_attribute_name(self, "Position");
    if(position == NULL)
        return;

    Attribute* xCoordinate = to_set_find_attribute_name(position, "xCoordinate");
    Attribute* yCoordinate = to_set_find_attribute_name(position, "yCoordinate");
    if(xCoordinate == NULL ||yCoordinate == NULL)
        return;

    char *args[] = {"vision"};

    _to_send_use_request(client, 1, args);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);

    if(useResponse.type != ATTRIBUTE_RESPONSE) {
        to_free_attribute(self);
        return;
    }

    TOAttributeResponse aResponse;
    to_recv_attribute_response(client->socket, &aResponse);

    char map[15][15];
    memset(map, '*', sizeof(map));

    for(int i = 0; i < aResponse.count; ++i) {
        Attribute* attribute = aResponse.attributes[i];
        if(attribute == NULL)
            continue;

        Attribute* thingPosition = to_set_find_attribute_name(attribute, "Position");
        if(thingPosition == NULL)
            continue;

        Attribute* thingXCoordinate = to_set_find_attribute_name(thingPosition, "xCoordinate");
        Attribute* thingYCoordinate = to_set_find_attribute_name(thingPosition, "yCoordinate");
        if(thingXCoordinate == NULL || thingYCoordinate == NULL)
            continue;

        long long xPos = (thingXCoordinate->value.value - xCoordinate->value.value) + 7;
        long long yPos = (thingYCoordinate->value.value - yCoordinate->value.value) + 7;

        if((xPos >= 0 && xPos <= 14) && (yPos >= 0 && yPos <= 14))
            map[14 - yPos][xPos] = '.';

        to_free_attribute(attribute);
    }

    map[7][7] = 'P';

    printf("Map around (15x15):\n");
    for(int y = 0; y < 15; ++y)
        printf("%.15s\n", map[y]);

    free(aResponse.attributes);
    to_free_attribute(self);
}
