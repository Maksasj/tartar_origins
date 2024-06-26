#include "to_client_connection_response.h"

int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response) {
    int length = recv(socket, (void*) response, sizeof(TOClientConnectionResponse), 0);

    if(length <= 0)
        return -1;

    if((response->info.success != 1) && (response->info.type != TO_CLIENT_CONNECTION_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

int to_send_client_connection_response(int socket) {
    TOClientConnectionResponse response;

    response.info.type = TO_CLIENT_CONNECTION_RESPONSE_PACKAGE;
    response.info.success = 1;

    send(socket, (void*) &response, sizeof(TOClientConnectionResponse), 0);

    return 1;
}
