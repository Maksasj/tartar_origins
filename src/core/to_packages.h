#ifndef _TO_CORE_PACKAGES_H_
#define _TO_CORE_PACKAGES_H_

typedef enum TOReqPackageType {
    TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE,
    TO_MAP_INFO_REQUEST_PACKAGE,
    TO_CHARACTER_INFO_REQUEST_PACKAGE
} TOReqPackageType;

typedef enum TOResPackageType {
    TO_MAP_INFO_RESPONSE_PACKAGE,
    TO_CHARACTER_INFO_RESPONSE_PACKAGE
} TOResPackageType;

// Request packages
typedef struct TOCharacterPosUpdateRequest {
    TOReqPackageType type;
    int newX;
    int newY;
} TOCharacterPosUpdateRequest;

typedef struct TOMapUpdateRequest {
    TOReqPackageType type;
} TOMapUpdateRequest;

typedef struct TOCharacterInfoRequest {
    TOReqPackageType type;
} TOCharacterInfoRequest;

// Response packages
typedef struct TOMapInfoResponse {
    TOReqPackageType type;
    char tiles[16][16];
} TOMapInfoResponse;

typedef struct TOCharacterInfoResponse {
    TOReqPackageType type;
    int posX;
    int posY;
} TOCharacterInfoResponse;

#endif