#ifndef _TO_CORE_USE_RESPONSE_PACKAGE_H_
#define _TO_CORE_USE_RESPONSE_PACKAGE_H_

#include "../to_res_package_info.h"
#include "to_backend.h"

typedef enum TOUseResponseType {
    EMPTY_RESPONSE,
    ENTITY_RESPONSE
} TOUseResponseType;

typedef struct TOUseResponse {
    TOResPackageInfo info;

    TOUseResponseType type;
} TOUseResponse;

int to_recv_use_response(int socket, TOUseResponse* response);
void to_send_use_response(int socket, TOUseResponseType type);

#endif