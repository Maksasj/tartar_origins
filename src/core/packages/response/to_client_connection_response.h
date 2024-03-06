#ifndef _TO_CORE_CLIENT_CONNECTION_RESPONSE_PACKAGE_H_
#define _TO_CORE_CLIENT_CONNECTION_RESPONSE_PACKAGE_H_

#include "../to_res_package_info.h"
#include "to_backend.h"

typedef struct TOClientConnectionResponse {
    TOResPackageInfo info;
} TOClientConnectionResponse;

int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response);
void to_send_client_connection_response(int socket);

#endif