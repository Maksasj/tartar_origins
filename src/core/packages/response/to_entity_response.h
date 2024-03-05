#ifndef _TO_CORE_ENTITY_RESPONSE_PACKAGE_H_
#define _TO_CORE_ENTITY_RESPONSE_PACKAGE_H_

#include "../to_res_package_info.h"
#include "to_backend.h"
#include "to_entity.h"

typedef struct TOEntityResponse {
    TOResPackageInfo info;

    unsigned int count;
    Entity** entity;
} TOEntityResponse;

int to_recv_entity_response(int socket, TOEntityResponse* response);
void to_send_entity_response(int socket, Entity* entity[], unsigned int count);

#endif