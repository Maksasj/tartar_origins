#include "to_client_command.h"

void to_client_sync_character_info(TOClient* client) {
    TOCharacterInfoRequest request;
    request.type = TO_CHARACTER_INFO_REQUEST_PACKAGE;
    send(client->socket, &request, sizeof(TOCharacterInfoRequest), 0);

    TOCharacterInfoResponse response;
    recv(client->socket, &response, sizeof(TOCharacterInfoResponse), 0);

    client->character->stats = response.stats;
    client->character->xPos = response.xPos;
    client->character->yPos = response.yPos;
}

void to_client_go_command_callback(TOClient* client, int argc, char* argv[]) {
    TOCharacterPosUpdateRequest request;
    request.type = TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE;

    request.newX = client->character->xPos;
    request.newY = client->character->yPos;

    if(argc > 1) {
        if(strcmp(argv[1], "up") == 0) {
            ++request.newY;
        } else if(strcmp(argv[1], "left") == 0) {
            --request.newX;
        } else if(strcmp(argv[1], "right") == 0) {
            ++request.newX;
        } else if(strcmp(argv[1], "down") == 0) {
            --request.newY;
        } else {
            printf("Wrong destination '%s'", argv[1]);
        }
    } else {
        printf("Wrong amount of arguments for 'go' command\n");
    }

    send(client->socket, &request, sizeof(TOCharacterPosUpdateRequest), 0);

    to_client_sync_character_info(client);

    Character* character = client->character;
    printf("Now staying at (X = %d, Y = %d)\n", character->xPos, character->yPos);
}

void to_client_stats_command_callback(TOClient* client, int argc, char* argv[]) {
    to_client_sync_character_info(client);

    Character* character = client->character;

    printf("Position: (X = %d, Y = %d)\n", character->xPos, character->yPos);
    printf("Stats:\n");
    printf("    Stamina %lld\n", character->stats.stamina);
    printf("    Strength %lld\n", character->stats.strength);
    printf("    Intellect %lld\n", character->stats.intellect);
    printf("    Armor %lld\n", character->stats.armor);
}

void to_client_map_command_callback(TOClient* client, int argc, char* argv[]) {
    Tile tiles[16][16];

    Character* character = client->character;

    for(int x = 0; x < 16; ++x) {
        for(int y = 0; y < 16; ++y) {
            TOTileInfoRequest request;

            request.type = TO_TILE_INFO_REQUEST_PACKAGE;
            request.xPos = character->xPos + (x - 8);
            request.yPos = character->yPos + (y - 8);

            send(client->socket, &request, sizeof(TOTileInfoRequest), 0);

            TOTileInfoResponse response;
            recv(client->socket, &response, sizeof(TOTileInfoResponse), 0);
            tiles[x][y] = response.tile;
        }
    }

    printf("Map around (16x16):\n");

    char characters[16][16];
    memset(character, '.', sizeof(characters));

    for(int x = 0; x < 16; ++x) {
        for(int y = 0; y < 16; ++y) {
            TileType type = tiles[x][y].type;

            if(type == VOID_TILE)
                characters[15 - y][x] = '.';
            else if(type == GROUND_TILE)
                characters[15 - y][x] = 'g';
            else if(type == WATER_TILE)
                characters[15 - y][x] = '~';
        }
    }

    for(int y = 0; y < 16; ++y)
        printf("%.16s\n", characters[y]);

    // Todo this think should not be there
    to_client_sync_character_info(client);
}
