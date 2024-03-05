#include "to_entity_response.h"

void _to_send_attribute(int socket, Attribute* attribute) {
    send(socket, attribute, sizeof(Attribute), 0);

    if(attribute->info.type != SET_ATTRIBUTE)
        return;

    for(int i = 0; i < attribute->set.count; ++i) {
        Attribute* at = attribute->set.attributes[i];

        if(at != NULL)
            _to_send_attribute(socket, at);
    }
}

Attribute* _to_recv_attribute(int socket) {
    Attribute* attribute = malloc(sizeof(Attribute));
    recv(socket, attribute, sizeof(Attribute), 0);

    if(attribute->info.type != SET_ATTRIBUTE)
        return attribute;

    for(int i = 0; i < attribute->set.count; ++i) {
        Attribute* at = attribute->set.attributes[i];

        if(at != NULL)
            attribute->set.attributes[i] = _to_recv_attribute(socket);
    }

    return attribute;
}

void _to_send_entity(int socket, Entity* entity) {
    send(socket, entity, sizeof(Entity), 0);
}

Entity* _to_recv_entity(int socket) {
    Entity* entity = malloc(sizeof(Entity));
    recv(socket, entity, sizeof(Entity), 0);
    return entity;
}

int to_recv_entity_response(int socket, TOEntityResponse* response) {
    recv(socket, response, sizeof(TOEntityResponse), 0);

    if(response->count <= 0)
        return -1;

    response->entity = malloc(sizeof(Entity*) * response->count);

    for(int e = 0; e < response->count; ++e) {
        Entity* entity = _to_recv_entity(socket);
        response->entity[e] = entity;

        for(int i = 0; i < entity->attributeCount; ++i)
            entity->attributes[i] = _to_recv_attribute(socket);
    }

    return 1;
}

void to_send_entity_response(int socket, Entity* entity[], unsigned int count) {
    TOEntityResponse response;

    response.info.type = TO_ENTITY_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.count = count;

    send(socket, &response, sizeof(TOEntityResponse), 0);

    for(int e = 0; e < count; ++e) {
        _to_send_entity(socket, entity[e]);

        for(int i = 0; i < entity[e]->attributeCount; ++i)
            _to_send_attribute(socket, entity[e]->attributes[i]);
    }
}
