#ifndef _TO_CORE_ATTRIBUTE_INFO_H_
#define _TO_CORE_ATTRIBUTE_INFO_H_

#include "to_attribute_type.h"

typedef struct AttributeInfo {
    AttributeType type;

    char name[16];

    unsigned int class;
    unsigned int variation;
} AttributeInfo;

#endif