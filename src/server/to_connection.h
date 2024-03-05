#ifndef _TO_SERVER_CONNECTION_H_
#define _TO_SERVER_CONNECTION_H_

#include "to_core.h"
#include "to_backend.h"

typedef struct Connection {
    // Threads
    thrd_t thread;

    // Networking
    int c_socket;
    struct sockaddr_in clientaddr;

    // Gameplay
    Entity* character;
} Connection;

Connection* to_new_connection(int socket, struct sockaddr_in clientaddr);

#endif