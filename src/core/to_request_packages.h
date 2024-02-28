#ifndef _TO_CORE_REQUEST_PACKAGES_H_
#define _TO_CORE_REQUEST_PACKAGES_H_

typedef enum TOReqPackageType {
    TO_CHARACTER_POSITION_UPDATE_REQUEST_PACKAGE,
    TO_MAP_INFO_REQUEST_PACKAGE,
    TO_CHARACTER_INFO_REQUEST_PACKAGE
} TOReqPackageType;

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

#endif