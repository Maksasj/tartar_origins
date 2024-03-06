#ifndef _TO_CORE_USE_REQUEST_PACKAGE_H_
#define _TO_CORE_USE_REQUEST_PACKAGE_H_

#include "../to_req_package_info.h"

typedef struct TOUseRequest {
    TOReqPackageInfo info;

    unsigned long long size;
    void* buffer;
} TOUseRequest;
void to_send_use_request(int socket, void* buffer, unsigned long long size);

#endif