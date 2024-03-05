#ifndef _TO_CORE_CLIENT_CONNECTION_REQUEST_PACKAGE_H_
#define _TO_CORE_CLIENT_CONNECTION_REQUEST_PACKAGE_H_

#include "../to_req_package_info.h"

// Request packages
typedef struct TOClientConnectionRequest {
    TOReqPackageInfo info;
} TOClientConnectionRequest;
void to_send_client_connection_request(int socket);

#endif