#ifndef _TO_CORE_RESPONSE_PACKAGE_INFO_H_
#define _TO_CORE_RESPONSE_PACKAGE_INFO_H_

typedef enum TOResPackageType {
    TO_CLIENT_CONNECTION_RESPONSE_PACKAGE,

    TO_USE_RESPONSE_PACKAGE,
    TO_ATTRIBUTE_RESPONSE_PACKAGE
} TOResPackageType;

typedef struct TOResPackageInfo {
    TOResPackageType type;
    int success;
} TOResPackageInfo;

#endif