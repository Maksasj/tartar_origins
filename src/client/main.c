#include "to_client.h"

#define BUFFLEN 1023

int main(int argc, char *argv[]){
    TOClient* client = to_new_client();

    to_client_connect(client, "127.0.0.1", 6969);

    while(1) {
        printf("Enter the message: ");

        char buffer[BUFFLEN];
        fgets(buffer, BUFFLEN, stdin);

        send(client->socket, buffer, strlen(buffer),0);

        memset(&buffer, 0, BUFFLEN);

        recv(client->socket, buffer, BUFFLEN, 0);
        printf("Server sent: %s\n", buffer);
    }

    close(client->socket);

    return 0;
}