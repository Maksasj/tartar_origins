#include "to_server.h"

TOServer* to_new_server(unsigned int port) {
    TOServer* server = malloc(sizeof(TOServer));

    server->world = to_create_world();
    to_world_create_chunk(server->world, 0, 0);

    server->connectionIndex = 0;
    memset(&server->connections, 0, sizeof(Connection*) * TO_SERVER_MAX_CONNECTIONS);

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    if ((server->socket = socket(AF_INET, SOCK_STREAM,0))< 0){
        fprintf(stderr,"ERROR #2: cannot create listening socket.\n");
        exit(1);
    }

    struct sockaddr_in servaddr; // Serverio adreso struktūra
    memset(&servaddr,0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // nurodomas protokolas (IP)

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port); // nurodomas portas

    if (bind(server->socket, (struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        fprintf(stderr,"ERROR #3: bind listening socket.\n");
        exit(1);
    }

    return server;
}

void to_server_listen(TOServer* server) {
    if (listen(server->socket, 5) <0){
        fprintf(stderr,"ERROR #4: error in listen().\n");
        exit(1);
    }
}

Connection* to_server_accept_connections(TOServer* server) {
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0, sizeof(clientaddr));

    socklen_t clientaddrlen = sizeof(struct sockaddr);
    int socket = accept(server->socket,(struct sockaddr*)&clientaddr,&clientaddrlen);

    if (socket < 0){
        fprintf(stderr,"ERROR #5: error occured accepting connection.\n");
        return NULL;
        // exit(1);
    }

    TOClientConnectionRequest request;
    recv(socket, &request, sizeof(TOClientConnectionRequest), 0);

    if(request.info.type != TO_CLIENT_CONNECTION_REQUEST_PACKAGE) {
        printf("First package is not a client connection package\n");
        return NULL;
    }

    Connection* connection = to_new_connection(socket, clientaddr);

    to_send_client_connection_response(socket);

    return connection;
}