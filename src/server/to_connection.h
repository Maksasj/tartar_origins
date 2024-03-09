#ifndef _TO_SERVER_CONNECTION_H_
#define _TO_SERVER_CONNECTION_H_

#include "to_core.h"
#include "to_backend.h"

typedef struct Connection {
    // Networking
    int socket;
    struct sockaddr_in clientaddr;

    // Gameplay
    Attribute* character;
} Connection;

Connection* to_new_connection(int socket, struct sockaddr_in clientaddr);
void to_free_connection(Connection* connection);

#endif