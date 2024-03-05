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
    TOUseRequest request;
    memcpy(&request, buffer, sizeof(TOUseRequest));

    if(request.argc <= 0)
        return;

    Entity* domain = handle->connection->character;
    unsigned int count = domain->attributeCount;

    unsigned long long entityCount = 0;
    Entity** entities = NULL;

    for(int i = 0; i < count; ++i) {
        Attribute* attribute = domain->attributes[i];

        if((attribute != NULL) && attribute->info.type == EFFECT_ATTRIBUTE) {
            EffectResult* result = attribute->effect.effect(attribute, domain, NULL, request.argc, request.argv);

            if(result == NULL)
                continue;

            if(entities == NULL) {
                entities = malloc(sizeof(Entity*) * result->count);
            } else {
                entities = realloc(entities, sizeof(Entity*) * (entityCount + result->count));
            }

            memcpy(entities + entityCount * sizeof(Entity*), result->entities, result->count * sizeof(Entity*));
            entityCount += result->count;

            to_free_effect_result(result);
        }
    }

    if(entityCount == 0) {
        to_send_use_response(handle->connection->c_socket, EMPTY_RESPONSE);
    } else {
        to_send_use_response(handle->connection->c_socket, ENTITY_RESPONSE);
        to_send_entity_response(handle->connection->c_socket, entities, entityCount);
    }

    free(entities);
}

int to_handle_client(void *ptr) {
    TOClientHandle* handle = (TOClientHandle*) ptr;
    Connection* connection = handle->connection;

    char buffer[1024];
    memset(&buffer, 0, sizeof(buffer));

    TOClientHandlePacketCallback callbacks[] = {
        { TO_CLIENT_CONNECTION_REQUEST_PACKAGE, NULL },
        { TO_USE_REQUEST_PACKAGE,               to_handle_use_request_packet }
    };
    unsigned long long callbackCount = sizeof(callbacks) / sizeof(TOClientHandlePacketCallback);

    while(1) {
        int length = recv(connection->c_socket, buffer, sizeof(buffer), 0);

        TOReqPackageType type;
        memcpy(&type, buffer, sizeof(TOReqPackageType));

        for(unsigned int i = 0; i < callbackCount; ++i) {
            if(type == callbacks[i].type) {
                callbacks[i].callback(handle, buffer, length);
                break;
            }
        }
    }

    close(connection->c_socket);

    return 0;
}
