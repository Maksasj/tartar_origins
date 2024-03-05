#include "to_client_connection_response.h"

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
