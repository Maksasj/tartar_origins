#ifndef _TO_CLIENT_H_
#define _TO_CLIENT_H_

#include "packages/to_packages.h"

#include "to_utils.h"
#include "to_backend.h"

typedef struct TOClient {
    int socket;
} TOClient;

int to_client_connect(TOClient* client, const char* api, unsigned long port);

TOClient* to_new_client();

void to_close_client(TOClient* client);
void to_free_client(TOClient* client);

#endif