#include "to_connection.h"

EffectResult* movement_callback(Attribute* effect, Attribute* domain, Attribute* target, void* buffer, unsigned long long length) {
    return NULL;
}

EffectResult* self_callback(Attribute* effect, Attribute* domain, Attribute* target, void* buffer, unsigned long long length) {
    char argv[16][16];
    memcpy(argv, buffer, sizeof(argv));

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

    connection->character = to_create_set_attribute("Self");

    connection->character->set.attributes[0] = to_create_tag_attribute("Player");
    connection->character->set.attributes[1] = to_create_effect_attribute("Movement", movement_callback);
    connection->character->set.attributes[2] = to_create_effect_attribute("Self", self_callback);

    Attribute* a3 = to_create_set_attribute("Stats");
    a3->set.count = 2;
    a3->set.attributes[0] = to_create_tag_attribute("Health");
    a3->set.attributes[1] = to_create_tag_attribute("Strength");
    connection->character->set.attributes[3] = a3;

    connection->character->set.count = 4;

    return connection;
}
