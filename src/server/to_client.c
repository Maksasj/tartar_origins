#include "to_client.h"

int handle_client(void *ptr) {
    Connection* connection = (Connection*) ptr;

    char buffer[1024];
    memset(&buffer,0,sizeof(buffer));

    while(1) {
        TOReqPackageType type;
        int len = recv(connection->c_socket, &type, sizeof(TOReqPackageType), 0);

        switch (type) {
            case TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE: {
                TOMapInfoResponse response;
                response.type = TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE;

                printf("TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE\n");
                break;
            };
            case TO_MAP_INFO_REQUEST_PACKAGE: {
                TOMapInfoResponse response;
                response.type = TO_MAP_INFO_REQUEST_PACKAGE;

                printf("TO_MAP_INFO_REQUEST_PACKAGE\n");
                break;
            };
            case TO_CHARACTER_INFO_REQUEST_PACKAGE: {
                TOMapInfoResponse response;
                response.type = TO_CHARACTER_INFO_REQUEST_PACKAGE;

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
