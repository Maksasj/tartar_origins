#ifndef _TO_CORE_REQUEST_PACKAGES_H_
#define _TO_CORE_REQUEST_PACKAGES_H_

#include "to_backend.h"

typedef enum TOReqPackageType {
    TO_CLIENT_CONNECTION_REQUEST_PACKAGE,

    TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE,
    TO_CHARACTER_INFO_REQUEST_PACKAGE,

    TO_TILE_INFO_REQUEST_PACKAGE,

    TO_NEAR_CREATURES_COUNT_REQUEST_PACKAGE,
    TO_NEAR_CREATURES_INFO_REQUEST_PACKAGE
} TOReqPackageType;

// Request packages
typedef struct TOClientConnectionRequest {
    TOReqPackageType type;
} TOClientConnectionRequest;
void to_send_client_connection_request(int socket);

typedef struct TOCharacterPosUpdateRequest {
    TOReqPackageType type;
    int newX;
    int newY;
} TOCharacterPosUpdateRequest;
void to_send_character_pos_update_request(int socket, long long xPos, long long yPos);

typedef struct TOTileInfoRequest {
    TOReqPackageType type;
    int xPos;
    int yPos;
} TOTileInfoRequest;
void to_send_tile_info_request(int socket, int xPos, int yPos);

typedef struct TOCharacterInfoRequest {
    TOReqPackageType type;
} TOCharacterInfoRequest;
void to_send_character_info_request(int socket);

typedef struct TONearCreaturesCountRequest {
    TOReqPackageType type;
} TONearCreaturesCountRequest;
void to_send_near_creatures_count_request(int socket);

typedef struct TONearCreaturesInfoRequest {
    TOReqPackageType type;

    unsigned int index;
} TONearCreaturesInfoRequest;
void to_send_near_creatures_info_request(int socket, unsigned int index);

#endif