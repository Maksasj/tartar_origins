#include "to_client_handle.h"

#include "to_server.h"

int to_handle_client_connection_request_packet(TOServer* server, Connection* con, void* buffer, unsigned long long length) {
    // Todo

    return -1;
}

int to_handle_use_request_packet(TOServer* server, Connection* con, void* buffer, unsigned long long length) {
    Attribute* domain = con->character;

    unsigned long long attributeCount = 0;
    Attribute** attributes = NULL;

    for(int i = 0; i < domain->set.count; ++i) {
        Attribute* attribute = domain->set.attributes[i];

        if((attribute == NULL) || attribute->info.type != EFFECT_ATTRIBUTE)
            continue;

        EffectContext context;
        context.effect = attribute;
        context.domain = domain;
        context.target= NULL;
        context.world = server->world;

        EffectResult* result = attribute->effect.effect(&context, buffer, length);

        if(result == NULL)
            continue;

        if(attributes == NULL)
            attributes = malloc(sizeof(Attribute*) * result->count);
        else
            attributes = realloc(attributes, sizeof(Attribute*) * (attributeCount + result->count));

        memcpy(attributes + attributeCount * sizeof(Attribute*), result->attributes, result->count * sizeof(Attribute*));
        attributeCount += result->count;

        to_free_effect_result(result);
    }

    if(attributeCount == 0) {
        if(to_send_use_response(con->socket, EMPTY_RESPONSE) == -1)
            return -1;
    } else {
        if(to_send_use_response(con->socket, ATTRIBUTE_RESPONSE) == -1)
            return -1;
        if(to_send_attribute_response(con->socket, attributes, attributeCount) == -1)
            return -1;
    }

    free(attributes);
    return 1;
}

int to_handle_client(TOServer* server, Connection* con) {
    TOClientHandlePacketCallback callbacks[] = {
        { TO_CLIENT_CONNECTION_REQUEST_PACKAGE, NULL },
        { TO_USE_REQUEST_PACKAGE,               to_handle_use_request_packet }
    };
    unsigned long long callbackCount = sizeof(callbacks) / sizeof(TOClientHandlePacketCallback);

    char buffer[1024];
    memset(&buffer, 0, sizeof(buffer));

    int length = recv(con->socket, buffer, sizeof(buffer), 0);

    if(length <= 0)
        return length;

    TOReqPackageType type;
    memcpy(&type, buffer, sizeof(TOReqPackageType));

    for(unsigned int i = 0; i < callbackCount; ++i) {
        if(type == callbacks[i].type) {
            int res = callbacks[i].callback(server, con, buffer + sizeof(TOUseRequest), length - sizeof(TOUseRequest));

            if(res == -1)
                return -1;

            break;
        }
    }

    return 1;
}
