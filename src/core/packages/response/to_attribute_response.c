#include "to_attribute_response.h"

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

int to_recv_attribute_response(int socket, TOAttributeResponse* response) {
    recv(socket, response, sizeof(TOAttributeResponse), 0);

    if(response->count <= 0)
        return -1;

    response->attributes = malloc(sizeof(Attribute*) * response->count);

    for(int e = 0; e < response->count; ++e)
        response->attributes[e] = _to_recv_attribute(socket);

    return 1;
}

void to_send_attribute_response(int socket, Attribute* attributes[], unsigned int count) {
    TOAttributeResponse response;

    response.info.type = TO_ATTRIBUTE_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.count = count;

    send(socket, &response, sizeof(TOAttributeResponse), 0);

    for(int e = 0; e < count; ++e)
        _to_send_attribute(socket, attributes[e]);
}
