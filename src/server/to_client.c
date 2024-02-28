#include "to_client.h"

int handle_client(void *ptr) {
    Connection* connection = (Connection*) ptr;

    char buffer[1024];
    memset(&buffer, 0, sizeof(buffer));

    while(1) {
        int len = recv(connection->c_socket, buffer, sizeof(buffer), 0);

        TOReqPackageType type;
        memcpy(&type, buffer, sizeof(TOReqPackageType));

        switch (type) {
            case TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE: {
                TOCharacterPosUpdateRequest request;
                memcpy(&request, buffer, sizeof(TOCharacterPosUpdateRequest));

                connection->character->xPos = request.newX;
                connection->character->yPos = request.newY;

                printf("TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE %d %d\n", request.newX, request.newY);
                break;
            };
            case TO_MAP_INFO_REQUEST_PACKAGE: {
                // TOMapInfoResponse request;
                // memcpy(&request, buffer, sizeof(TOMapInfoResponse));

                printf("TO_MAP_INFO_REQUEST_PACKAGE\n");
                break;
            };
            case TO_CHARACTER_INFO_REQUEST_PACKAGE: {
                TOCharacterInfoResponse response;
                response.type = TO_CHARACTER_INFO_RESPONSE_PACKAGE;
                response.stats = connection->character->stats;
                response.xPos = connection->character->xPos;
                response.yPos = connection->character->yPos;

                send(connection->c_socket, &response, sizeof(TOCharacterInfoResponse), 0);

                printf("TO_CHARACTER_INFO_REQUEST_PACKAGE\n");
                break;
            };
        }

        // int r_len = send(connection->c_socket,buffer, len,0);

        // printf("IP: %s Sent: %d Received: %d\n", inet_ntoa(connection->clientaddr.sin_addr), len, r_len);
    }

    close(connection->c_socket);

    return 0;
}
