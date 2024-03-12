#ifndef _TO_CORE_USE_REQUEST_PACKAGE_H_
#define _TO_CORE_USE_REQUEST_PACKAGE_H_

#include "../../attribute/to_attribute.h"
#include "../to_req_package_info.h"

typedef struct TOUseRequest {
    TOReqPackageInfo info;

    EffectUse use;
} TOUseRequest;
void to_send_use_request(int socket, char id[16], void* buffer, unsigned long long size);

#endif