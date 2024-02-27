/*
 * Echo klientas
 *
 * Author: Kęstutis Mizara
 * Description: Išsiunčia serveriui pranešimą ir jį gauna
 */

#ifdef _WIN32
#include <winsock2.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFLEN 1024

int main(int argc, char *argv[]){
#ifdef _WIN32
    WSADATA data;
#endif
    unsigned int port;
    int s_socket;
    struct sockaddr_in servaddr; // Serverio adreso struktūra

    char buffer[BUFFLEN];

    port = 6969;
#ifdef _WIN32
    WSAStartup(MAKEWORD(2,2),&data);
#endif

    /*
     * Sukuriamas socket'as
     */
    if ((s_socket = socket(AF_INET, SOCK_STREAM,0))< 0){
        fprintf(stderr,"ERROR #2: cannot create socket.\n");
        exit(1);
    }

    /*
     * Išvaloma ir užpildoma serverio struktūra
     */
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET; // nurodomas protokolas (IP)
    servaddr.sin_port = htons(port); // nurodomas portas

    /*
     * Išverčiamas simbolių eilutėje užrašytas ip į skaitinę formą ir
     * nustatomas serverio adreso struktūroje.
     */
    #ifdef _WIN32
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    #else
        if ( inet_aton(argv[1], &servaddr.sin_addr) <= 0 ) {
            fprintf(stderr,"ERROR #3: Invalid remote IP address.\n");
            exit(1);
        }
    #endif

    if (connect(s_socket,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        fprintf(stderr,"ERROR #4: error in connect().\n");
        exit(1);
    }

    for(;;) {
        printf("Enter the message: ");
        fgets(buffer, BUFFLEN, stdin);

        send(s_socket,buffer,strlen(buffer),0);

        memset(&buffer,0,BUFFLEN);

        recv(s_socket,buffer,BUFFLEN,0);
        printf("Server sent: %s\n", buffer);
    }

    close(s_socket);

    return 0;
}