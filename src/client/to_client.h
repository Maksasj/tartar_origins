#ifndef _TO_CLIENT_H_
#define _TO_CLIENT_H_

#include "packages/to_packages.h"

#include "to_backend.h"

typedef struct TOClient {
    int socket;

    Entity* character;
} TOClient;

int to_client_connect(TOClient* client, const char* api, unsigned long port);

TOClient* to_new_client();

#endif