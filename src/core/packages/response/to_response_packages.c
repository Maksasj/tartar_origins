#include "to_response_packages.h"

int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response) {
    recv(socket, response, sizeof(TOClientConnectionResponse), 0);

    if(response->type != TO_CLIENT_CONNECTION_RESPONSE_PACKAGE)
        return -1;

    return 1;
}

int to_recv_character_info_response(int socket, TOCharacterInfoResponse* response) {
    recv(socket, response, sizeof(TOCharacterInfoResponse), 0);

    if(response->type != TO_CHARACTER_INFO_RESPONSE_PACKAGE)
        return -1;

    return 1;
}

int to_recv_tile_info_response(int socket, TOTileInfoResponse* response) {
    recv(socket, response, sizeof(TOTileInfoResponse), 0);

    if(response->type != TO_TILE_INFO_RESPONSE_PACKAGE)
        return -1;

    return 1;
}

int to_recv_near_creatures_count_response(int socket, TONearCreaturesCountResponse* response) {
    recv(socket, response, sizeof(TONearCreaturesCountResponse), 0);

    if(response->type != TO_NEAR_CREATURES_COUNT_RESPONSE_PACKAGE)
        return -1;

    return 1;
}

int to_recv_creature_info_response(int socket, TOCreatureInfoResponse* response) {
    recv(socket, response, sizeof(TOCreatureInfoResponse), 0);

    if(response->type != TO_CREATURE_INFO_RESPONSE_PACKAGE)
        return -1;

    return 1;
}
