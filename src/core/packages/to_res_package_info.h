#ifndef _TO_CORE_RESPONSE_PACKAGE_INFO_H_
#define _TO_CORE_RESPONSE_PACKAGE_INFO_H_

typedef enum TOResPackageType {
    TO_CLIENT_CONNECTION_RESPONSE_PACKAGE,

    TO_ENTITY_RESPONSE_PACKAGE,

    /*
    TO_CHARACTER_INFO_RESPONSE_PACKAGE,

    TO_TILE_INFO_RESPONSE_PACKAGE,

    TO_NEAR_CREATURES_COUNT_RESPONSE_PACKAGE,
    TO_CREATURE_INFO_RESPONSE_PACKAGE
    */
} TOResPackageType;

typedef struct TOResPackageInfo {
    TOResPackageType type;
    int success;
} TOResPackageInfo;

#endif