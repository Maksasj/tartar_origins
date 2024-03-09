#include "to_attribute_response.h"

int _to_send_attribute(int socket, Attribute* attribute) {
    int length = send(socket, (void*) attribute, sizeof(Attribute), 0);

    if(length == -1)
        return -1;

    if(attribute->info.type != SET_ATTRIBUTE)
        return 1;

    for(int i = 0; i < attribute->set.count; ++i) {
        Attribute* at = attribute->set.attributes[i];

        if(at != NULL) {
            length = _to_send_attribute(socket, at);

            if(length == -1)
                return -1;
        }
    }

    return 1;
}

Attribute* _to_recv_attribute(int socket) {
    Attribute* attribute = malloc(sizeof(Attribute));
    recv(socket, (void*) attribute, sizeof(Attribute), 0);

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
    int length = recv(socket, (void*) response, sizeof(TOAttributeResponse), 0);

    if(length <= 0)
        return -1;

    if(response->count <= 0)
        return -1;

    response->attributes = malloc(sizeof(Attribute*) * response->count);

    for(int e = 0; e < response->count; ++e)
        response->attributes[e] = _to_recv_attribute(socket);

    return 1;
}

int to_send_attribute_response(int socket, Attribute* attributes[], unsigned int count) {
    TOAttributeResponse response;

    response.info.type = TO_ATTRIBUTE_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.count = count;

    int length = send(socket, (void*) &response, sizeof(TOAttributeResponse), 0);

    if(length == -1)
        return -1;

    for(int e = 0; e < count; ++e) {
        length = _to_send_attribute(socket, attributes[e]);

        if(length == -1)
            return -1;
    }

    return 1;
}
