#include "to_use_request.h"

void to_send_use_request(int socket, unsigned int argc, char argv[16][16]) {
    TOUseRequest request;

    request.info.type = TO_USE_REQUEST_PACKAGE;
    request.info.success = 1;

    request.argc = argc;
    for(int i = 0; i < argc; ++i)
        strcpy(request.argv[i], argv[i]);

    send(socket, &request, sizeof(TOUseRequest), 0);
}