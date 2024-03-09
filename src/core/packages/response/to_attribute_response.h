#ifndef _TO_CORE_ATTRIBUTE_RESPONSE_PACKAGE_H_
#define _TO_CORE_ATTRIBUTE_RESPONSE_PACKAGE_H_

#include "../to_res_package_info.h"
#include "attribute/to_attributes.h"
#include "to_backend.h"

typedef struct TOAttributeResponse {
    TOResPackageInfo info;

    unsigned int count;
    Attribute** attributes;
} TOAttributeResponse;

int to_recv_attribute_response(int socket, TOAttributeResponse* response);
int to_send_attribute_response(int socket, Attribute* attributes[], unsigned int count);

#endif