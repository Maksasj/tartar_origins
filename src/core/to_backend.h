#ifndef _TO_SERVER_BACKEND_H_
#define _TO_SERVER_BACKEND_H_

#ifdef _WIN32
    // #include <winsock.h>
    #include <WinSock2.h>
    #define socklen_t int
    #include <io.h>
#else
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    
    #include <sys/timerfd.h>

    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif