#include "to_client_connection_request.h"

void to_send_client_connection_request(int socket) {
    TOClientConnectionRequest request;

    request.info.type = TO_CLIENT_CONNECTION_REQUEST_PACKAGE;
    request.info.success = 1;

    send(socket, (void*) &request, sizeof(TOClientConnectionRequest), 0);
}
