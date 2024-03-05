#ifndef _TO_CORE_REQUEST_PACKAGES_H_
#define _TO_CORE_REQUEST_PACKAGES_H_

#include "../to_req_package_info.h"

#include "to_backend.h"

// Request packages
typedef struct TOClientConnectionRequest {
    TOReqPackageInfo info;
} TOClientConnectionRequest;
void to_send_client_connection_request(int socket);

typedef struct TOUseRequest {
    TOReqPackageInfo info;

    unsigned int argc;
    char argv[16][16];
} TOUseRequest;
void to_send_use_request(int socket, unsigned int argc, char argv[16][16]);

#endif