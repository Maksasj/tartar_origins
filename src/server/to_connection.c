#include "to_connection.h"


void movement_callback(union Attribute* effect, struct Entity* domain, struct Entity* target, unsigned int argc, char argv[16][16]) {
    printf("Used something\n");
}

Connection* to_new_connection(int socket, struct sockaddr_in clientaddr) {
    Connection* connection = malloc(sizeof(Connection));

    connection->c_socket = socket;
    memcpy(&connection->clientaddr, &clientaddr, sizeof(clientaddr));

    connection->character = to_create_entity(0, 0);

    Attribute* a0 = to_create_tag_attribute("Player");
    to_entity_add_attribute(connection->character, a0);

    Attribute* a1 = to_create_effect_attribute("Movement", movement_callback);
    to_entity_add_attribute(connection->character, a1);

    to_entity_stringify(connection->character);

    return connection;
}
