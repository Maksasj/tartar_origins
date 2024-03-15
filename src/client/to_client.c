#include "to_client.h"

int to_client_connect(TOClient* client, const char* api, unsigned long port) {
    struct sockaddr_in servaddr;

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    #ifdef _WIN32
        servaddr.sin_addr.s_addr = inet_addr(api);
    #else
        if (inet_aton(api, &servaddr.sin_addr) <= 0) {
            TO_LOG(TO_ERROR, "Invalid remote IP adreess");
            return -1;
        }
    #endif

    for(;;) {
        if (connect(client->socket, (struct sockaddr*)&servaddr, sizeof(servaddr)) >= 0)
            break;

        TO_LOG(TO_INFO, "Could not connect to server, trying again");
    }

    to_send_client_connection_request(client->socket);

    TOClientConnectionResponse response;
    int result = to_recv_client_connection_response(client->socket, &response);

    if(result == -1)
        return -1;

    return response.info.success;
}

TOClient* to_new_client() {
    TOClient* client = malloc(sizeof(TOClient));

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    client->socket = socket(AF_INET, SOCK_STREAM,0);

    if(client->socket < 0)
        return NULL;

    return client;
}

void to_close_client(TOClient* client) {
    #ifdef _WIN32
        shutdown(client->socket, SD_BOTH);
        if(closesocket(client->socket) == SOCKET_ERROR)
            TO_LOG(TO_ERROR, "Failed to close socket");
    #else
        close(client->socket);
    #endif
}

void to_free_client(TOClient* client) {
    free(client);
}
