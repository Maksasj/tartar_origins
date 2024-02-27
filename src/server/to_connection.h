#ifndef _TO_SERVER_CONNECTION_H_
#define _TO_SERVER_CONNECTION_H_

#include "to_backend.h"

typedef struct Connection {
    thrd_t thread;

    int c_socket;
    struct sockaddr_in clientaddr;
} Connection;

#endif