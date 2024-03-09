#ifndef _TO_CORE_GODLY_HAND_ATTRIBUTE_H_
#define _TO_CORE_GODLY_HAND_ATTRIBUTE_H_

#include "../to_attribute.h"

#include "to_position_attribute.h"
#include "to_world.h"

#define WALK_DISTANCE 1

EffectResult* _to_godly_hand_attribute_callback(EffectContext* context, void* buffer, unsigned long long length);
Attribute* to_create_godly_hand_attribute();

#endif