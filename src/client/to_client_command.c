#include "to_client_command.h"

void _to_send_use_request(TOClient* client, int argc, char* argv[]) {
    char arguments[16][16];
    for(int i = 0; i < 16; ++i)
        memset(arguments[i], '\0', 16);

    for(int i = 0; i < argc; ++i)
        strcpy(arguments[i], argv[i]);

    to_send_use_request(client->socket, arguments, sizeof(arguments));
}

void to_client_get_self_callback(TOClient* client, int argc, char* argv[]) {
    char *args[] = {"self"};

    _to_send_use_request(client, 1, args);

    TOUseResponse useResponse;
    to_recv_use_response(client->socket, &useResponse);

    if(useResponse.type == ATTRIBUTE_RESPONSE) {
        TOAttributeResponse aResponse;
        to_recv_attribute_response(client->socket, &aResponse);

        for (int i = 0; i < aResponse.count; ++i) {
            to_attribute_stringify(aResponse.attributes[i]);
            to_free_attribute(aResponse.attributes[i]);
        }

        free(aResponse.attributes);
    }
}

void to_client_use_callback(TOClient* client, int argc, char* argv[]) {
    _to_send_use_request(client, argc, argv);

    TOUseResponse response;
    to_recv_use_response(client->socket, &response);
}
