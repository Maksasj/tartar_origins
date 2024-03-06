#include "to_use_request.h"

void to_send_use_request(int socket, void* buffer, unsigned long long size) {
    TOUseRequest request;

    request.info.type = TO_USE_REQUEST_PACKAGE;
    request.info.success = 1;
    request.size = size;

    void* response = malloc(sizeof(TOUseRequest) + size);
    memcpy(response, &request, sizeof(TOUseRequest));
    memcpy(response + sizeof(TOUseRequest), buffer, size);

    send(socket, response, sizeof(TOUseRequest) + size, 0);

    free(response);
}