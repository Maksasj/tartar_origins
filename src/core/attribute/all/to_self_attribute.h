#ifndef _TO_CORE_SELF_ATTRIBUTE_H_
#define _TO_CORE_SELF_ATTRIBUTE_H_

#include "../to_attribute.h"

EffectResult* _to_self_attribute_callback(Attribute* effect, Attribute* domain, Attribute* target, void* buffer, unsigned long long length);
Attribute* to_create_self_attribute();

#endif