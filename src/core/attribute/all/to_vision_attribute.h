#ifndef _TO_CORE_VISION_ATTRIBUTE_H_
#define _TO_CORE_VISION_ATTRIBUTE_H_

#include "../to_attribute.h"

#define VISION_DISTANCE 8

EffectResult* _to_vision_attribute_callback(EffectContext* context, void* buffer, unsigned long long length);
Attribute* to_create_vision_attribute();

#endif