#include "to_use_response.h"

int to_recv_use_response(int socket, TOUseResponse* response) {
    int length = recv(socket, (void*) response, sizeof(TOUseResponse), 0);

    if(length <= 0)
        return -1;

    if((response->info.success != 1) && (response->info.type != TO_USE_RESPONSE_PACKAGE))
        return -1;

    return 1;
}

int to_send_use_response(int socket, TOUseResponseType type) {
    TOUseResponse response;

    response.info.type = TO_USE_RESPONSE_PACKAGE;
    response.info.success = 1;

    response.type = type;

    int length = send(socket, (void*) &response, sizeof(TOUseResponse), 0);
    
    if(length == -1)
        return -1;

    return 1;
}