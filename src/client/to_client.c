#include "to_client.h"

int to_client_connect(TOClient* client, const char* api, unsigned long port) {
    struct sockaddr_in servaddr;

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    #ifdef _WIN32
        servaddr.sin_addr.s_addr = inet_addr(api);
    #else
        if ( inet_aton(argv[1], &servaddr.sin_addr) <= 0 ) {
            fprintf(stderr,"ERROR #3: Invalid remote IP address.\n");
            exit(1);
        }
    #endif

    if (connect(client->socket, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        fprintf(stderr,"ERROR #4: error in connect().\n");
        return 0;
    }

    // There we handle connection packages
    to_send_client_connection_request(client->socket);

    TOClientConnectionResponse response;
    to_recv_client_connection_response(client->socket, &response);

    if(response.success) {
        client->character = malloc(sizeof(Character));
        *client->character = response.character;
    }

    return response.success;
}

TOClient* to_new_client() {
    TOClient* client = malloc(sizeof(TOClient));

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    client->socket = socket(AF_INET, SOCK_STREAM,0);

    if (client->socket < 0) {
        fprintf(stderr,"ERROR #2: cannot create socket.\n");
        exit(1);
    }

    return client;
}
