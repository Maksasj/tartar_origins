#ifndef _TO_SERVER_CLIENT_H_
#define _TO_SERVER_CLIENT_H_

#include "to_connection.h"
#include "to_backend.h"

#include "to_packages.h"

struct TOServer;

typedef struct TOClientHandle {
    struct TOServer* server;
    Connection* connection;
} TOClientHandle;

TOClientHandle* to_create_client_handle(struct TOServer* server, Connection* connection);

int handle_client(void *ptr);

#endif