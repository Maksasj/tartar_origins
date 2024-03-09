#include "to_server.h"

#define SERVER_PORT 6969

int main() {
    TOServer* server = to_new_server(SERVER_PORT);
    TO_LOG(TO_INFO, "Successfully created server on port '%d'", SERVER_PORT);

    to_server_listen(server);
    TO_LOG(TO_INFO, "Started listening");

    fd_set readSet;

    while(1) {
        FD_ZERO(&readSet);

        int maxFd = server->socket;
        FD_SET(server->socket, &readSet);

        for(int i = 0; i < TO_SERVER_MAX_CONNECTIONS; ++i) {
            if(server->connections[i] == NULL)
                continue;

            int socket = server->connections[i]->socket;
            FD_SET(socket, &readSet);

            if(socket > maxFd)
                maxFd = socket;
        }

        select(maxFd + 1, &readSet, NULL , NULL, NULL);

        if(FD_ISSET(server->socket, &readSet)){
            Connection* con = to_server_accept_connections(server);

            int slot = to_server_find_connection_slot(server);

            if(slot == -1)
                TO_LOG(TO_WARNING, "Server is full, could not accept new connection from '%s'", inet_ntoa(con->clientaddr.sin_addr));

            server->connections[slot] = con;

            TO_LOG(TO_INFO, "Server accepted connection from '%s'", inet_ntoa(con->clientaddr.sin_addr));
        }

        for(int i = 0; i < TO_SERVER_MAX_CONNECTIONS; ++i) {
            Connection* con = server->connections[i];

            if(con == NULL)
                continue;

            int socket = con->socket;

            if(!FD_ISSET(socket, &readSet))
                continue;

            int result = to_handle_client(server, con);

            printf("result: '%d'\n", result);

            if(result == 0) {
                TO_LOG(TO_INFO, "Closing connection with '%s'", inet_ntoa(con->clientaddr.sin_addr));
                close(con->socket);

                to_free_connection(con);
                server->connections[i] = NULL;
                continue;
            }

            if(result < 0) {
                TO_LOG(TO_INFO, "Receive error from '%s'", inet_ntoa(con->clientaddr.sin_addr));
                close(con->socket);

                to_free_connection(con);
                server->connections[i] = NULL;
                continue;
            }
        }
    }

    return 0;
}