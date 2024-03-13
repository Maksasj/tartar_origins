#include "to_connection.h"

Connection* to_new_connection(int socket, struct sockaddr_in clientaddr) {
    Connection* connection = malloc(sizeof(Connection));

    connection->socket = socket;
    memcpy(&connection->clientaddr, &clientaddr, sizeof(clientaddr));

    Attribute* self = to_create_set_attribute("Player");

    to_set_append_attribute(self, to_create_self_attribute());
    to_set_append_attribute(self, to_create_vision_attribute());
    to_set_append_attribute(self, to_create_movement_attribute());
    to_set_append_attribute(self, to_create_godly_hand_attribute());
    to_set_append_attribute(self, to_create_position_attribute(0, 0));
    to_set_append_attribute(self, to_create_tag_attribute("Humanoid"));
    to_set_append_attribute(self, to_create_value_attribute("Health", 10));

    Attribute* hand = to_create_set_attribute("Hand");

    Attribute* sword = to_create_set_attribute("Sword");
    to_set_append_attribute(sword, to_create_value_attribute("Damage", 5));
    to_set_append_attribute(sword, to_create_slashing_attribute());

    to_set_append_attribute(hand, sword);
    to_set_append_attribute(self, hand);

    connection->character = self;

    return connection;
}

void to_free_connection(Connection* connection) {
    if(connection == NULL)
        return;

    if(connection->character != NULL)
        to_free_attribute(connection->character);

    free(connection);
}