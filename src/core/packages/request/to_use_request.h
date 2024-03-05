#ifndef _TO_CORE_USE_REQUEST_PACKAGE_H_
#define _TO_CORE_USE_REQUEST_PACKAGE_H_

#include "../to_req_package_info.h"

typedef struct TOUseRequest {
    TOReqPackageInfo info;

    unsigned int argc;
    char argv[16][16];
} TOUseRequest;
void to_send_use_request(int socket, unsigned int argc, char argv[16][16]);

#endif