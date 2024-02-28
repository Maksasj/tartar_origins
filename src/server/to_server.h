#ifndef _TO_SERVER_H_
#define _TO_SERVER_H_

#include "to_backend.h"
#include "to_client.h"
#include "to_connection.h"

#define TO_SERVER_MAX_CONNECTIONS 256

typedef struct TOServer {
    // Server socket;
    int socket;

    // Active connections
    Connection* connections[TO_SERVER_MAX_CONNECTIONS];
    unsigned int connectionIndex;
} TOServer;

TOServer* to_new_server(unsigned int port);

void to_server_listen(TOServer* server);

Connection* to_server_accept_connections(TOServer* server);

#endif