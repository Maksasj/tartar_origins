#ifndef _TO_CORE_POSITION_ATTRIBUTE_H_
#define _TO_CORE_POSITION_ATTRIBUTE_H_

#include "../to_attribute.h"

#include "to_position_attribute.h"

Attribute* to_create_position_attribute(long long xCord, long long yCord);

int _to_get_position(Attribute* domain, long long* xCord, long long* yCord);
int _to_set_position(Attribute* domain, long long xCord, long long yCord);

#endif