#include "to_use_request.h"

void to_send_use_request(int socket, char id[16], void* buffer, unsigned long long size) {
    TOUseRequest request;

    request.info.type = TO_USE_REQUEST_PACKAGE;
    request.info.success = 1;

    memcpy(request.use.id, id, sizeof(char) * 16);

    if(buffer == NULL)
        size = 0;

    request.use.size = size;

    void* response = malloc(sizeof(TOUseRequest) + size);
    memcpy(response, &request, sizeof(TOUseRequest));

    if(buffer != NULL)
        memcpy(response + sizeof(TOUseRequest), buffer, size);

    send(socket, (void*) response, sizeof(TOUseRequest) + size, 0);

    free(response);
}