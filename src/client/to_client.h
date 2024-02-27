#ifndef _TO_CLIENT_H_
#define _TO_CLIENT_H_

#include "to_backend.h"

typedef struct TOClient {
    int socket;
} TOClient;

void to_client_connect(TOClient* client, const char* api, unsigned long port);

TOClient* to_new_client();

#endif