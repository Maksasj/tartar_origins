#include "to_connection.h"

Connection* to_new_connection(int socket, struct sockaddr_in clientaddr) {
    Connection* connection = malloc(sizeof(Connection));

    connection->c_socket = socket;
    memcpy(&connection->clientaddr, &clientaddr, sizeof(clientaddr));

    connection->character = to_create_set_attribute("Self");

    connection->character->set.attributes[0] = to_create_tag_attribute("Player");
    connection->character->set.attributes[1] = to_create_self_attribute();
    connection->character->set.attributes[2] = to_create_vision_attribute();
    connection->character->set.attributes[3] = to_create_movement_attribute();
    connection->character->set.attributes[4] = to_create_position_attribute(0, 0);

    connection->character->set.count = 5;

    return connection;
}
