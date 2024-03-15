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

    // 1 Second timer
    int timer1s = timerfd_create(CLOCK_REALTIME,  0);
    struct itimerspec spec1s = { { 1, 0 }, { 1, 0 } };
    timerfd_settime(timer1s, 0, &spec1s, NULL);

    // 3 Minutes timer
    int timer3m = timerfd_create(CLOCK_REALTIME,  0);
    struct itimerspec spec3m = { { 3, 0 }, { 3, 0 } };
    timerfd_settime(timer3m, 0, &spec3m, NULL);

    for(;;) {
        FD_ZERO(&socketSet);

        int maxFd = server->socket;
        FD_SET(server->socket, &socketSet);

        FD_SET(timer1s, &socketSet);
        if(timer1s > maxFd)
            maxFd = timer1s;

        FD_SET(timer3m, &socketSet);
        if(timer3m > maxFd)
            maxFd = timer3m;

        for(int i = 0; i < TO_SERVER_MAX_PLAYERS; ++i) {
            if(server->connections[i] == NULL)
                continue;

            int socket = server->connections[i]->socket;
            FD_SET(socket, &socketSet);

            if(socket > maxFd)
                maxFd = socket;
        }

        select(maxFd + 1, &socketSet, NULL , NULL, NULL);

        // There we handle 1 second regular actions
        if(FD_ISSET(timer1s, &socketSet)) {

            timerfd_settime(timer1s, 0, &spec1s, NULL);
        }

        // There we handle 3 minutes regular actions
        if(FD_ISSET(timer3m, &socketSet)) {
            
            timerfd_settime(timer3m, 0, &spec3m, NULL);
        }

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