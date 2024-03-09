#include "to_server.h"

TOServer* to_new_server(unsigned int port) {
    TOServer* server = malloc(sizeof(TOServer));

    server->world = to_create_world();
    to_world_create_chunk(server->world, 0, 0);

    memset(&server->connections, 0, sizeof(Connection*) * TO_SERVER_MAX_CONNECTIONS);

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    if ((server->socket = socket(AF_INET, SOCK_STREAM,0))< 0) {
        TO_LOG(TO_ERROR, "Cannot create listening socket.");
        exit(1);
    }

    struct sockaddr_in servaddr; // Serverio adreso struktūra
    memset(&servaddr,0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // nurodomas protokolas (IP)

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port); // nurodomas portas

    if (bind(server->socket, (struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        TO_LOG(TO_ERROR, "Failed to bind listening socket");
        exit(1);
    }

    return server;
}

void to_server_listen(TOServer* server) {
    if (listen(server->socket, 5) <0) {
        TO_LOG(TO_ERROR, "Error in listen()");
        exit(1);
    }
}

int to_server_find_connection_slot(TOServer* server) {
    for(int i = 0; i < TO_SERVER_MAX_CONNECTIONS; ++i)
        if(server->connections[i] == NULL)
            return i;

    return -1;
}

Connection* to_server_accept_connections(TOServer* server) {
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0, sizeof(clientaddr));

    socklen_t clientaddrlen = sizeof(struct sockaddr);
    int socket = accept(server->socket,(struct sockaddr*)&clientaddr,&clientaddrlen);

    if (socket < 0){
        TO_LOG(TO_ERROR, "Error occurred accepting connection");
        return NULL;
    }

    TOClientConnectionRequest request;
    recv(socket, (void*) &request, sizeof(TOClientConnectionRequest), 0);

    if(request.info.type != TO_CLIENT_CONNECTION_REQUEST_PACKAGE) {
        TO_LOG(TO_WARNING, "First package is not a client connection package");
        return NULL;
    }

    Connection* connection = to_new_connection(socket, clientaddr);

    to_send_client_connection_response(socket);

    return connection;
}