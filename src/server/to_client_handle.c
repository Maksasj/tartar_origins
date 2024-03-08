#include "to_client_handle.h"

#include "to_server.h"

TOClientHandle* to_create_client_handle(struct TOServer* server, Connection* connection) {
    TOClientHandle* handle = malloc(sizeof(TOClientHandle));

    handle->server = server;
    handle->connection = connection;

    return handle;
}

void to_handle_client_connection_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    // Todo
}

void to_handle_use_request_packet(TOClientHandle* handle, void* buffer, unsigned long long length) {
    Attribute* domain = handle->connection->character;
    unsigned int count = domain->set.count;

    unsigned long long attributeCount = 0;
    Attribute** attributes = NULL;

    for(int i = 0; i < count; ++i) {
        Attribute* attribute = domain->set.attributes[i];

        if((attribute == NULL) || attribute->info.type != EFFECT_ATTRIBUTE)
            continue;

        EffectContext context;
        context.effect = attribute;
        context.domain = domain;
        context.target= NULL;
        context.world = handle->server->world;

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
        to_send_use_response(handle->connection->socket, EMPTY_RESPONSE);
    } else {
        to_send_use_response(handle->connection->socket, ATTRIBUTE_RESPONSE);
        to_send_attribute_response(handle->connection->socket, attributes, attributeCount);
    }

    free(attributes);
}

int to_handle_client(void *ptr) {
    TOClientHandle* handle = (TOClientHandle*) ptr;
    Connection* connection = handle->connection;

    TOClientHandlePacketCallback callbacks[] = {
        { TO_CLIENT_CONNECTION_REQUEST_PACKAGE, NULL },
        { TO_USE_REQUEST_PACKAGE,               to_handle_use_request_packet }
    };
    unsigned long long callbackCount = sizeof(callbacks) / sizeof(TOClientHandlePacketCallback);

    char buffer[1024];
    memset(&buffer, 0, sizeof(buffer));

    while(1) {
        int length = recv(connection->socket, buffer, sizeof(buffer), 0);

        TOReqPackageType type;
        memcpy(&type, buffer, sizeof(TOReqPackageType));

        for(unsigned int i = 0; i < callbackCount; ++i) {
            if(type == callbacks[i].type) {
                callbacks[i].callback(handle, buffer + sizeof(TOUseRequest), length - sizeof(TOUseRequest));
                break;
            }
        }
    }

    close(connection->socket);

    return 0;
}
