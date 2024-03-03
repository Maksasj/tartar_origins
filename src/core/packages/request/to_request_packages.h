#ifndef _TO_CORE_REQUEST_PACKAGES_H_
#define _TO_CORE_REQUEST_PACKAGES_H_

#include "../to_req_package_info.h"

#include "to_backend.h"

// Request packages
typedef struct TOClientConnectionRequest {
    TOReqPackageInfo info;
} TOClientConnectionRequest;
void to_send_client_connection_request(int socket);

typedef struct TOGetSelfEntityRequest {
    TOReqPackageInfo info;
} TOGetSelfEntityRequest;
void to_send_get_self_entity_request(int socket);

typedef struct TOUseRequest {
    TOReqPackageInfo info;

    unsigned int argc;
    char argv[16][16];
} TOUseRequest;
void to_send_use_request(int socket, unsigned int argc, char argv[16][16]);

/*
typedef struct TOCharacterPosUpdateRequest {
    TOReqPackageInfo info;

    int newX;
    int newY;
} TOCharacterPosUpdateRequest;
void to_send_character_pos_update_request(int socket, long long xPos, long long yPos);

typedef struct TOTileInfoRequest {
    TOReqPackageInfo info;

    int xPos;
    int yPos;
} TOTileInfoRequest;
void to_send_tile_info_request(int socket, int xPos, int yPos);

typedef struct TOCharacterInfoRequest {
    TOReqPackageInfo info;
} TOCharacterInfoRequest;
void to_send_character_info_request(int socket);

typedef struct TONearCreaturesCountRequest {
    TOReqPackageInfo info;
} TONearCreaturesCountRequest;
void to_send_near_creatures_count_request(int socket);

typedef struct TONearCreaturesInfoRequest {
    TOReqPackageInfo info;

    unsigned int index;
} TONearCreaturesInfoRequest;
void to_send_near_creatures_info_request(int socket, unsigned int index);
*/

#endif