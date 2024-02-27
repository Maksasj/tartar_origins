/*
 * Echo serveris
 *
 * Author: Kęstutis Mizara
 * Description: Gauna kliento pranešimą ir išsiunčia atgal
 */

#ifdef _WIN32
    #include <winsock2.h>
    #define socklen_t int
    #include <io.h>
#else
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tinycthread.h>

typedef struct Connection {
    int c_socket;
    struct sockaddr_in clientaddr;
} Connection;

int print_message_function(void *ptr) {
    Connection* connection = (Connection*) ptr;

    char buffer[1024];
    memset(&buffer,0,sizeof(buffer));

    for(;;) {
        int s_len = recv(connection->c_socket, buffer,sizeof(buffer),0);
        int r_len = send(connection->c_socket,buffer,s_len,0);

        printf("IP: %s Sent: %d Received: %d\n", inet_ntoa(connection->clientaddr.sin_addr), s_len, r_len);
    }

    close(connection->c_socket);

    return 0;
}

void start_server(int* l_socket) {
    unsigned int port = 6969;
    // int l_socket; // socket'as skirtas prisijungimų laukimui

    struct sockaddr_in servaddr; // Serverio adreso struktūra

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    /*
     * Sukuriamas serverio socket'as
     */
    if ((*l_socket = socket(AF_INET, SOCK_STREAM,0))< 0){
        fprintf(stderr,"ERROR #2: cannot create listening socket.\n");
        exit(1);
    }

    /*
     * Išvaloma ir užpildoma serverio adreso struktūra
     */
    memset(&servaddr,0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // nurodomas protokolas (IP)

    /*
     * Nurodomas IP adresas, kuriuo bus laukiama klientų, šiuo atveju visi
     * esami sistemos IP adresai (visi interfeis'ai)
     */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port); // nurodomas portas

    /*
     * Serverio adresas susiejamas su socket'u
     */
    if (bind (*l_socket, (struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        fprintf(stderr,"ERROR #3: bind listening socket.\n");
        exit(1);
    }
}

int main(int argc, char *argv []){
    int l_socket;

    start_server(&l_socket);

    /*
     * Nurodoma, kad socket'u l_socket bus laukiama klientų prisijungimo,
     * eilėje ne daugiau kaip 5 aptarnavimo laukiantys klientai
     */
    if (listen(l_socket, 5) <0){
        fprintf(stderr,"ERROR #4: error in listen().\n");
        exit(1);
    }

    thrd_t threads[10];
    int threadIndex = 0;

    for(;;){
        struct sockaddr_in clientaddr; // Prisijungusio kliento adreso struktūra
        memset(&clientaddr,0, sizeof(clientaddr));

        int c_socket; // prisijungusio kliento socket'as

        socklen_t clientaddrlen = sizeof(struct sockaddr);
        if ((c_socket = accept(l_socket,(struct sockaddr*)&clientaddr,&clientaddrlen))<0){
            fprintf(stderr,"ERROR #5: error occured accepting connection.\n");
            exit(1);
        }

        Connection* connection = malloc(sizeof(Connection));
        connection->c_socket = c_socket;
        memcpy(&connection->clientaddr, &clientaddr, sizeof(clientaddr));

        if (thrd_create(&threads[threadIndex], print_message_function, (void*) connection) != thrd_success) {
            printf("Error:unable to create thread 1");
            return 1;
        } else {
            ++threadIndex;
        }

        // thrd_join(thread1, NULL);
        // thrd_join(thread2, NULL);
    }

    return 0;
}