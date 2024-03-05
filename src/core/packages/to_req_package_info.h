#ifndef _TO_CORE_REQUEST_PACKAGE_INFO_H_
#define _TO_CORE_REQUEST_PACKAGE_INFO_H_

#include "to_backend.h"

typedef enum TOReqPackageType {
    TO_CLIENT_CONNECTION_REQUEST_PACKAGE,
    TO_USE_REQUEST_PACKAGE
} TOReqPackageType;

typedef struct TOReqPackageInfo {
    TOReqPackageType type;
    int success;
} TOReqPackageInfo;

#endif