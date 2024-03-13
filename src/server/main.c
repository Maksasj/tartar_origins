#include "to_server.h"

#define SERVER_PORT 6969

int main() {
    TOServer* server = to_new_server(SERVER_PORT);
    if(server == NULL) {
        TO_LOG(TO_ERROR, "Cannot create server");
        return 1;
    }

    TO_LOG(TO_INFO, "Successfully created server on port '%d'", SERVER_PORT);

    if(to_server_listen(server) == -1)
        return 1;

    TO_LOG(TO_INFO, "Started listening");

    fd_set socketSet;

    for(;;) {
        FD_ZERO(&socketSet);

        int maxFd = server->socket;
        FD_SET(server->socket, &socketSet);

        for(int i = 0; i < TO_SERVER_MAX_PLAYERS; ++i) {
            if(server->connections[i] == NULL)
                continue;

            int socket = server->connections[i]->socket;
            FD_SET(socket, &socketSet);

            if(socket > maxFd)
                maxFd = socket;
        }

        select(maxFd + 1, &socketSet, NULL , NULL, NULL);

        if(FD_ISSET(server->socket, &socketSet)){
            Connection* con = to_server_accept_connections(server);

            int slot = to_server_find_connection_slot(server);

            if(slot == -1) // Todo we need to disconnect our user properly
                TO_LOG(TO_WARNING, "Server is full, could not accept new connection from '%s'", inet_ntoa(con->clientaddr.sin_addr));

            server->connections[slot] = con;

            TO_LOG(TO_INFO, "Server accepted connection from '%s'", inet_ntoa(con->clientaddr.sin_addr));
        }

        for(int i = 0; i < TO_SERVER_MAX_PLAYERS; ++i) {
            Connection* con = server->connections[i];

            if(con == NULL)
                continue;

            int socket = con->socket;

            if(!FD_ISSET(socket, &socketSet))
                continue;

            if(to_handle_client(server, con) > 0)
                continue;

            TO_LOG(TO_INFO, "Closing connection with '%s'", inet_ntoa(con->clientaddr.sin_addr));

            #ifdef _WIN32
                shutdown(con->socket, SD_BOTH);
                if(closesocket(socket) == SOCKET_ERROR)
                    TO_LOG(TO_ERROR, "Failed to close socket");
            #else
                close(socket);
            #endif

            if(!to_world_terminate_creature(server->world, con->character))
                TO_LOG(TO_WARNING, "Failed to terminate disconnected player creature");

            con->character = NULL;

            to_free_connection(con);
            server->connections[i] = NULL;
        }
    }

    return 0;
}