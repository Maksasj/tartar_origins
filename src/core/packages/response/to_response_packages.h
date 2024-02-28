#ifndef _TO_CORE_RESPONSE_PACKAGES_H_
#define _TO_CORE_RESPONSE_PACKAGES_H_

#include "to_backend.h"
#include "to_character.h"
#include "to_world.h"

typedef enum TOResPackageType {
    TO_CLIENT_CONNECTION_RESPONSE_PACKAGE,

    TO_CHARACTER_INFO_RESPONSE_PACKAGE,

    TO_TILE_INFO_RESPONSE_PACKAGE,

    TO_NEAR_CREATURES_COUNT_RESPONSE_PACKAGE,
    TO_CREATURE_INFO_RESPONSE_PACKAGE
} TOResPackageType;

// Response packages
typedef struct TOClientConnectionResponse {
    TOResPackageType type;

    int success;

    Character character;
} TOClientConnectionResponse;
int to_recv_client_connection_response(int socket, TOClientConnectionResponse* response);

typedef struct TOCharacterInfoResponse {
    TOResPackageType type;

    StatBlock stats;
    int xPos;
    int yPos;
} TOCharacterInfoResponse;
int to_recv_character_info_response(int socket, TOCharacterInfoResponse* response);

typedef struct TOTileInfoResponse {
    TOResPackageType type;
    Tile tile;
} TOTileInfoResponse;
int to_recv_tile_info_response(int socket, TOTileInfoResponse* response);

typedef struct TONearCreaturesCountResponse {
    TOResPackageType type;

    unsigned int count;
} TONearCreaturesCountResponse;
int to_recv_near_creatures_count_response(int socket, TONearCreaturesCountResponse* response);

typedef struct TOCreatureInfoResponse {
    TOResPackageType type;

    int success;

    Creature creature;
} TOCreatureInfoResponse;

int to_recv_creature_info_response(int socket, TOCreatureInfoResponse* response);

#endif