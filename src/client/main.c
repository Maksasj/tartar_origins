#include "to_client.h"

#define BUFFLEN 1023

int main(int argc, char *argv[]){
    TOClient* client = to_new_client();

    to_client_connect(client, "127.0.0.1", 6969);

    while(1) {
        // printf("Enter the message: ");
//
        // char buffer[BUFFLEN];
        // fgets(buffer, BUFFLEN, stdin);

        /*
        {
            TOCharacterPosUpdateRequest request;
            request.type = TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE;
            send(client->socket, &request, sizeof(TOCharacterPosUpdateRequest),0);
        }

        {
            TOMapUpdateRequest request;
            request.type = TO_MAP_INFO_REQUEST_PACKAGE;
            send(client->socket, &request, sizeof(TOMapUpdateRequest),0);
        }
        */

        {
            TOCharacterInfoRequest request;
            request.type = TO_CHARACTER_INFO_REQUEST_PACKAGE;
            send(client->socket, &request, sizeof(TOCharacterInfoRequest),0);
        }

        printf("Send\n");

        // memset(&buffer, 0, BUFFLEN);

        // recv(client->socket, buffer, BUFFLEN, 0);
        // printf("Server sent: %s\n", buffer);
    }

    close(client->socket);

    return 0;
}