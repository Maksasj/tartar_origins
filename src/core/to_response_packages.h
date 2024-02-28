#ifndef _TO_CORE_RESPONSE_PACKAGES_H_
#define _TO_CORE_RESPONSE_PACKAGES_H_

#include "to_character.h"

typedef enum TOResPackageType {
    TO_CLIENT_CONNECTION_RESPONSE_PACKAGE,

    TO_MAP_INFO_RESPONSE_PACKAGE,
    TO_CHARACTER_INFO_RESPONSE_PACKAGE
} TOResPackageType;

// Response packages
typedef struct TOClientConnectionResponse {
    TOResPackageType type;

    int success;

    Character character;
} TOClientConnectionResponse;

typedef struct TOMapInfoResponse {
    TOResPackageType type;

    char tiles[16][16];
} TOMapInfoResponse;

typedef struct TOCharacterInfoResponse {
    TOResPackageType type;

    StatBlock stats;
    int xPos;
    int yPos;
} TOCharacterInfoResponse;

#endif