#include "to_request_packages.h"

void to_send_client_connection_request(int socket) {
    TOClientConnectionRequest request;
    request.type = TO_CLIENT_CONNECTION_REQUEST_PACKAGE;
    send(socket, &request, sizeof(TOClientConnectionRequest), 0);
}

void to_send_character_pos_update_request(int socket, long long xPos, long long yPos) {
    TOCharacterPosUpdateRequest request;
    request.type = TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE;

    request.newX = xPos;
    request.newY = yPos;

    send(socket, &request, sizeof(TOCharacterPosUpdateRequest), 0);
}

void to_send_tile_info_request(int socket, int xPos, int yPos) {
    TOTileInfoRequest request;

    request.type = TO_TILE_INFO_REQUEST_PACKAGE;
    request.xPos = xPos;
    request.yPos = yPos;

    send(socket, &request, sizeof(TOTileInfoRequest), 0);
}

void to_send_character_info_request(int socket) {
    TOCharacterInfoRequest request;
    request.type = TO_CHARACTER_INFO_REQUEST_PACKAGE;
    send(socket, &request, sizeof(TOCharacterInfoRequest), 0);
}

void to_send_near_creatures_count_request(int socket) {
    TONearCreaturesCountRequest request;
    request.type = TO_NEAR_CREATURES_COUNT_REQUEST_PACKAGE;
    send(socket, &request, sizeof(TONearCreaturesCountRequest), 0);
}

void to_send_near_creatures_info_request(int socket, unsigned int index) {
    TONearCreaturesInfoRequest request;

    request.type = TO_NEAR_CREATURES_INFO_REQUEST_PACKAGE;
    request.index = index;

    send(socket, &request, sizeof(TONearCreaturesInfoRequest), 0);
}
