#include "to_server.h"

TOServer* to_new_server(unsigned int port) {
    TOServer* server = malloc(sizeof(TOServer));
    memset(server->connections, 0, sizeof(Connection*) * TO_SERVER_MAX_PLAYERS);

    World* world = to_create_world();
    server->world = world;

    for(int x = -8; x < 8; ++x)
        for(int y = -8; y < 8; ++y)
            to_world_create_chunk(world, x, y);

    // Summon sample monster
    Attribute* monster = to_create_set_attribute("Slime");
    to_set_append_attribute(monster, to_create_tag_attribute("Monster"));
    to_set_append_attribute(monster, to_create_position_attribute(1, 1));
    to_set_append_attribute(monster, to_create_value_attribute("Health", 5));
    to_world_summon_creature(world, monster);

    // Summon gods
    to_world_summon_gods(world);

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    if ((server->socket = socket(AF_INET, SOCK_STREAM,0))< 0) {
        TO_LOG(TO_ERROR, "Cannot create listening socket.");
        return NULL;
    }

    struct sockaddr_in servaddr;
    memset(&servaddr,0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(server->socket, (struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
        TO_LOG(TO_ERROR, "Failed to bind listening socket");
        return NULL;
    }

    return server;
}

int to_server_listen(TOServer* server) {
    if (listen(server->socket, TO_SERVER_BACKLOG) <0) {
        TO_LOG(TO_ERROR, "Error in listen()");
        return -1;
    }

    return 1;
}

int to_server_find_connection_slot(TOServer* server) {
    for(int i = 0; i < TO_SERVER_MAX_PLAYERS; ++i)
        if(server->connections[i] == NULL)
            return i;

    return -1;
}

Connection* to_server_accept_connections(TOServer* server) {
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));

    int clientAddrLen = sizeof(struct sockaddr);
    int socket = accept(server->socket, (struct sockaddr*) &clientAddr, &clientAddrLen);

    if (socket < 0){
        TO_LOG(TO_ERROR, "Error occurred accepting connection");
        return NULL;
    }

    TOClientConnectionRequest request;
    int result = recv(socket, (void*) &request, sizeof(TOClientConnectionRequest), 0);

    if(result <= -1)
        return NULL;

    if(request.info.type != TO_CLIENT_CONNECTION_REQUEST_PACKAGE) {
        TO_LOG(TO_WARNING, "First package is not a client connection package");
        return NULL;
    }

    to_send_client_connection_response(socket);

    Connection* connection = to_new_connection(socket, clientAddr);

    to_world_summon_creature(server->world, connection->character);

    return connection;
}