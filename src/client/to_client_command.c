#include "to_client_command.h"

void to_client_go_command_callback(TOClient* client, int argc, char* argv[]) {
    TOCharacterPosUpdateRequest request;
    request.type = TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE;
    request.newY = -69;
    request.newX = 420;

    send(client->socket, &request, sizeof(TOCharacterPosUpdateRequest), 0);
}

void to_client_stats_command_callback(TOClient* client, int argc, char* argv[]) {
    TOCharacterInfoRequest request;
    request.type = TO_CHARACTER_INFO_REQUEST_PACKAGE;
    send(client->socket, &request, sizeof(TOCharacterInfoRequest), 0);

    TOCharacterInfoResponse response;
    recv(client->socket, &response, sizeof(TOCharacterInfoResponse), 0);

    printf("Position: (X = %d, Y = %d)\n", response.posX, response.posY);
    printf("Stats:\n");
    printf("    Stamina %lld\n", response.stats.stamina);
    printf("    Strength %lld\n", response.stats.strength);
    printf("    Intellect %lld\n", response.stats.intellect);
    printf("    Armor %lld\n", response.stats.armor);
}

void to_client_map_command_callback(TOClient* client, int argc, char* argv[]) {
    TOMapUpdateRequest request;
    request.type = TO_MAP_INFO_REQUEST_PACKAGE;
    send(client->socket, &request, sizeof(TOMapUpdateRequest), 0);
}
