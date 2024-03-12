#include "to_client_handle.h"

#include "to_server.h"

int to_handle_client_connection_request_packet(TOServer* server, Connection* con, void* buffer, unsigned long long length) {
    // Todo

    return -1;
}

void _to_propagate_use(TOServer* server, Attribute* domain, void* buffer, unsigned long long length, Attribute*** attributes, unsigned long long* attributeCount) {
    if(domain->info.type != SET_ATTRIBUTE)
        return;

    // Prepare player list
    Attribute* players[TO_SERVER_MAX_PLAYERS];

    for(int p = 0; p < TO_SERVER_MAX_PLAYERS; ++p) {
        if(server->connections[p] != NULL)
            players[p] = server->connections[p]->character;
        else
            players[p] = NULL;
    }

    for(int i = 0; i < domain->set.count; ++i) {
        Attribute* attribute = domain->set.attributes[i];

        if(attribute == NULL)
            continue;

        if(attribute->info.type == SET_ATTRIBUTE)
            _to_propagate_use(server, attribute, buffer, length, attributes, attributeCount);

        if(attribute->info.type != EFFECT_ATTRIBUTE)
            continue;

        // Prepare effect context
        EffectContext context;
        context.effect = attribute;
        context.domain = domain;
        context.target= NULL;
        context.world = server->world;
        context.players = players;

        EffectResult* result = attribute->effect.effect(&context, buffer, length);

        if(result == NULL)
            continue;

        if(*attributes == NULL)
            *attributes = malloc(sizeof(Attribute*) * result->count);
        else
            *attributes = realloc(*attributes, sizeof(Attribute*) * (*attributeCount + result->count));

        memcpy(*attributes + *attributeCount * sizeof(Attribute*), result->attributes, result->count * sizeof(Attribute*));
        *attributeCount += result->count;

        to_free_effect_result(result);
    }
}

int to_handle_use_request_packet(TOServer* server, Connection* con, void* buffer, unsigned long long length) {
    unsigned long long attributeCount = 0;
    Attribute** attributes = NULL;

    _to_propagate_use(server, con->character, buffer, length, &attributes, &attributeCount);

    if(attributeCount == 0 || attributes == NULL) {
        if(to_send_use_response(con->socket, EMPTY_RESPONSE) == -1)
            return -1;
    } else {
        if(to_send_use_response(con->socket, ATTRIBUTE_RESPONSE) == -1)
            return -1;
        if(to_send_attribute_response(con->socket, attributes, attributeCount) == -1)
            return -1;
    }

    if(attributes != NULL)
        free(attributes);

    return 1;
}

TOClientHandlePacketCallback callbacks[] = {
    { TO_CLIENT_CONNECTION_REQUEST_PACKAGE, NULL },
    { TO_USE_REQUEST_PACKAGE,               to_handle_use_request_packet }
};
unsigned long long callbackCount = sizeof(callbacks) / sizeof(TOClientHandlePacketCallback);

int to_handle_client(TOServer* server, Connection* con) {
    char buffer[1024] = { 0 };
    int length = recv(con->socket, buffer, sizeof(buffer), 0);

    if(length <= 0)
        return length;

    TOReqPackageType type;
    memcpy(&type, buffer, sizeof(TOReqPackageType));

    for(unsigned int i = 0; i < callbackCount; ++i) {
        if(type != callbacks[i].type)
            continue;

        int res = callbacks[i].callback(server, con, buffer + sizeof(TOUseRequest), length - sizeof(TOUseRequest));

        if(res == -1)
            return -1;

        break;
    }

    return 1;
}
