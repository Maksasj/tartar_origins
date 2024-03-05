#ifndef _TO_CORE_CLIENT_CONNECTION_RESPONSE_PACKAGE_H_
#define _TO_CORE_CLIENT_CONNECTION_RESPONSE_PACKAGE_H_

#include "../to_res_package_info.h"
#include "to_backend.h"
#include "to_entity.h"

typedef struct TOClientConnectionResponse {
    TOResPackageInfo info;

    Entity character;
} TOClientConnectionResponse;

int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response);
void to_send_client_connection_response(int socket, Entity character);

#endif