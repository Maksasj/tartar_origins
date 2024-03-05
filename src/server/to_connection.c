#include "to_connection.h"

EffectResult* movement_callback(Attribute* effect, Entity* domain, Entity* target, unsigned int argc, char argv[16][16]) {
    printf("Used something\n");

    return NULL;
}

EffectResult* self_callback(Attribute* effect, Entity* domain, Entity* target, unsigned int argc, char argv[16][16]) {
    if(strcmp(argv[0], "self") != 0)
        return NULL;

    EffectResult* result = to_create_effect_result();

    to_append_effect_result(result, domain);

    return result;
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

    Attribute* a2 = to_create_effect_attribute("Self", self_callback);
    to_entity_add_attribute(connection->character, a2);

    Attribute* a3 = to_create_set_attribute("Stats");
    a3->set.count = 2;
    a3->set.attributes[0] = to_create_tag_attribute("Health");
    a3->set.attributes[1] = to_create_tag_attribute("Strength");
    to_entity_add_attribute(connection->character, a3);

    to_entity_stringify(connection->character);

    return connection;
}
