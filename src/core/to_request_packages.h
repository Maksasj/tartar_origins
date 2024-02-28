#ifndef _TO_CORE_REQUEST_PACKAGES_H_
#define _TO_CORE_REQUEST_PACKAGES_H_

typedef enum TOReqPackageType {
    TO_CLIENT_CONNECTION_REQUEST_PACKAGE,

    TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE,
    TO_CHARACTER_INFO_REQUEST_PACKAGE,

    TO_TILE_INFO_REQUEST_PACKAGE,
} TOReqPackageType;

// Request packages
typedef struct TOClientConnectionRequest {
    TOReqPackageType type;
} TOClientConnectionRequest;

typedef struct TOCharacterPosUpdateRequest {
    TOReqPackageType type;
    int newX;
    int newY;
} TOCharacterPosUpdateRequest;

typedef struct TOTileInfoRequest {
    TOReqPackageType type;
    int xPos;
    int yPos;
} TOTileInfoRequest;

typedef struct TOCharacterInfoRequest {
    TOReqPackageType type;
} TOCharacterInfoRequest;

#endif