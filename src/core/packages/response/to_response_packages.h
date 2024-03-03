#ifndef _TO_CORE_RESPONSE_PACKAGES_H_
#define _TO_CORE_RESPONSE_PACKAGES_H_

#include "../to_res_package_info.h"

#include "to_backend.h"
#include "to_entity.h"
#include "to_world.h"

// Response packages
typedef struct TOClientConnectionResponse {
    TOResPackageInfo info;

    Entity character;
} TOClientConnectionResponse;
int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response);
void to_send_client_connection_response(int socket, Entity character);

void to_send_entity_response(int socket, Entity* entity);
Entity* to_recv_entity_response(int socket);

/*
typedef struct TOCharacterInfoResponse {
    TOResPackageInfo info;

    // StatBlock stats;
    int xPos;
    int yPos;
} TOCharacterInfoResponse;
int to_recv_character_info_response(int socket, TOCharacterInfoResponse* response);
void to_send_character_info_response(int socket, int xPos, int yPos);

typedef struct TOTileInfoResponse {
    TOResPackageInfo info;

    // Tile tile;
} TOTileInfoResponse;
int to_recv_tile_info_response(int socket, TOTileInfoResponse* response);
void to_send_tile_info_response(int socket);

typedef struct TONearCreaturesCountResponse {
    TOResPackageInfo info;

    unsigned int count;
} TONearCreaturesCountResponse;
int to_recv_near_creatures_count_response(int socket, TONearCreaturesCountResponse* response);
void to_send_near_creatures_response(int socket, unsigned int count);

typedef struct CreatureInfo {
    int xPos;
    int yPos;
} CreatureInfo;

typedef struct TOCreatureInfoResponse {
    TOResPackageInfo info;

    CreatureInfo creature;
} TOCreatureInfoResponse;
int to_recv_creature_info_response(int socket, TOCreatureInfoResponse* response);
void to_send_creature_info_response(int socket, CreatureInfo info);
*/

#endif