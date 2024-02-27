#include "to_client.h"

#define BUFFLEN 1023

int main(int argc, char *argv[]){
    TOClient* client = to_new_client();

    to_client_connect(client, "127.0.0.1", 6969);

    while(1) {
        char input[BUFFLEN];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Error or end of input
            break;
        }

        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        char *token = strtok(input, " ");
        if (token == NULL) {
            printf("Invalid command\n");
            continue;
        }

        if (strcmp(token, "go") == 0) {
            token = strtok(NULL, " ");
            if (token == NULL) {
                printf("Invalid command\n");
                continue;
            }

            TOCharacterPosUpdateRequest request;
            request.type = TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE;
            send(client->socket, &request, sizeof(TOCharacterPosUpdateRequest),0);
        } else if (strcmp(token, "stats") == 0) {
            TOCharacterInfoRequest request;
            request.type = TO_CHARACTER_INFO_REQUEST_PACKAGE;
            send(client->socket, &request, sizeof(TOCharacterInfoRequest),0);
        } else if (strcmp(token, "map") == 0) {
            TOMapUpdateRequest request;
            request.type = TO_MAP_INFO_REQUEST_PACKAGE;
            send(client->socket, &request, sizeof(TOMapUpdateRequest),0);
        } else {
            printf("Invalid command\n");
        }

        printf("Send\n");

        // memset(&buffer, 0, BUFFLEN);

        // recv(client->socket, buffer, BUFFLEN, 0);
        // printf("Server sent: %s\n", buffer);
    }

    close(client->socket);

    return 0;
}