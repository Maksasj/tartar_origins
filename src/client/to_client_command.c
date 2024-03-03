#include "to_client_command.h"

void to_client_get_self_entity_callback(TOClient* client, int argc, char* argv[]) {
    to_send_get_self_entity_request(client->socket);

    Entity* self = to_recv_entity_response(client->socket);

    to_entity_stringify(self);

    to_free_entity(self);
}

void to_client_use_callback(TOClient* client, int argc, char* argv[]) {
    if(argc <= 1)
        return;

    char arguments[16][16];
    for(int i = 0; i < 16; ++i)
        memset(arguments[i], '\0', 16);

    for(int i = 0; i < argc - 1; ++i)
        strcpy(arguments[i], argv[i + 1]);

    to_send_use_request(client->socket, argc - 1, arguments);
}

/*
void to_client_sync_character_info(TOClient* client) {
    to_send_character_info_request(client->socket);

    TOCharacterInfoResponse response;
    to_recv_character_info_response(client->socket, &response);

    // client->character->stats = response.stats;
    client->character->xPos = response.xPos;
    client->character->yPos = response.yPos;
}

void to_client_go_command_callback(TOClient* client, int argc, char* argv[]) {
    if(argc <= 1) {
        printf("Wrong amount of arguments for 'go' command\n");
        return;
    }

    if(strcmp(argv[1], "up") == 0) {
        to_send_character_pos_update_request(client->socket, client->character->xPos, client->character->yPos + 1);
    } else if(strcmp(argv[1], "left") == 0) {
        to_send_character_pos_update_request(client->socket, client->character->xPos - 1, client->character->yPos);
    } else if(strcmp(argv[1], "right") == 0) {
        to_send_character_pos_update_request(client->socket, client->character->xPos + 1, client->character->yPos);
    } else if(strcmp(argv[1], "down") == 0) {
        to_send_character_pos_update_request(client->socket, client->character->xPos, client->character->yPos - 1);
    } else {
        printf("Wrong destination '%s'", argv[1]);
    }

    to_client_sync_character_info(client);

    Entity* character = client->character;
    printf("Now staying at (X = %lld, Y = %lld)\n", character->xPos, character->yPos);

    to_client_map_command_callback(client, argc, argv);
}



void to_client_stats_command_callback(TOClient* client, int argc, char* argv[]) {
    // Entity* self = to_recv_entity(client->socket);

    // to_send_character_info_request(client->socket);

    // to_recv_character_info_response(client->socket, &response);

    // to_client_sync_character_info(client);

    // Entity* character = client->character;

    // printf("Position: (X = %lld, Y = %lld)\n", character->xPos, character->yPos);
    // printf("Stats:\n");
    // printf("    Stamina %lld\n", character->stats.stamina);
    // printf("    Strength %lld\n", character->stats.strength);
    // printf("    Intellect %lld\n", character->stats.intellect);
    // printf("    Armor %lld\n", character->stats.armor);
}

void to_client_map_command_callback(TOClient* client, int argc, char* argv[]) {
    Entity* character = client->character;

    // Tile tiles[15][15];

    char map[15][15];
    memset(map, '.', sizeof(map));

    for(int x = 0; x < 15; ++x) {
        for(int y = 0; y < 15; ++y) {
            to_send_tile_info_request(client->socket, character->xPos + (x - 7), character->yPos + (y - 7));

            TOTileInfoResponse response;
            to_recv_tile_info_response(client->socket, &response);
            // tiles[x][y] = response.tile;
        }
    }

    // Draw tiles
    for(int x = 0; x < 15; ++x) {
        for(int y = 0; y < 15; ++y) {
            TileType type = tiles[x][y].type;

            if(type == VOID_TILE)
                map[14 - y][x] = '*';
            else if(type == GROUND_TILE)
                map[14 - y][x] = ',';
            else if(type == WATER_TILE)
                map[14 - y][x] = '~';
        }
    }

    // Draw player
    map[7][7] = 'P';

    // Draw near creatures
    to_send_near_creatures_count_request(client->socket);

    TONearCreaturesCountResponse response;
    to_recv_near_creatures_count_response(client->socket, &response);

    printf("Near creatures: %d\n", response.count);

    for(int i = 0; i < response.count; ++i) {
        to_send_near_creatures_info_request(client->socket, i);

        TOCreatureInfoResponse response;
        to_recv_creature_info_response(client->socket, &response);

        if(!response.info.success)
            break;

        long long xPos = (response.creature.xPos - character->xPos) + 7;
        long long yPos = (response.creature.yPos - character->yPos) + 7;

        if((xPos >= 0 && xPos <= 14) && (yPos >= 0 && yPos <= 14)) {
            map[14 - yPos][xPos] = 'A';

            // if(response.creature.type == MONSTER_CREATURE) {
            //     map[14 - yPos][xPos] = 'M';
            // } else if(response.creature.type == PLAYER_CREATURE) {
            //     map[14 - yPos][xPos] = 'C';
            // }
        }
    }

    printf("Map around (15x15):\n");

    for(int y = 0; y < 15; ++y)
        printf("%.15s\n", map[y]);

    // Todo this think should not be there
    // to_client_sync_character_info(client);
}
*/
