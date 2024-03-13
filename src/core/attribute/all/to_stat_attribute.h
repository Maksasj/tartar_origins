#ifndef _TO_CORE_STAT_ATTRIBUTE_H_
#define _TO_CORE_STAT_ATTRIBUTE_H_

#include "../to_attribute.h"

Attribute* to_create_stat_attribute(char name[16], long long initialValue);

long long _to_stat_traverse(Attribute* attribute, char name[16]);

#endif