#include "to_connection.h"

Connection* to_new_connection(int socket, struct sockaddr_in clientaddr) {
    Connection* connection = malloc(sizeof(Connection));

    connection->c_socket = socket;
    memcpy(&connection->clientaddr, &clientaddr, sizeof(clientaddr));

    connection->character = to_create_character(WARRIOR);

    return connection;
}
