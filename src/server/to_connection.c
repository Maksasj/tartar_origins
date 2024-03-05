#include "to_connection.h"

EffectResult* movement_callback(Attribute* effect, Entity* domain, Entity* target, unsigned int argc, char argv[16][16]) {
    printf("Used something\n");

    return NULL;
}

EffectResult* self_callback(Attribute* effect, Entity* domain, Entity* target, unsigned int argc, char argv[16][16]) {
    if(strcmp(argv[0], "self") != 0)
        return NULL;

    EffectResult* result = to_create_effect_result();


    printf("Cool !\n");

    to_append_effect_result(result, domain);

    to_entity_stringify(result->entities[0]);

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

    to_entity_stringify(connection->character);

    return connection;
}
