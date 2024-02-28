#include "to_server.h"

int main() {
    TOServer* server = to_new_server(6969);

    to_server_listen(server);

    while(1) {
        Connection* con = to_server_accept_connections(server);

        if (thrd_create(&con->thread, handle_client, (void*) con) != thrd_success) {
            printf("Error:unable to create thread 1");
            return 1;
        }

        server->connections[server->connectionIndex] = con;
        ++server->connectionIndex;

        // thrd_join(thread1, NULL);
        // thrd_join(thread2, NULL);
    }

    return 0;
}