#ifndef _TO_CORE_MOVEMENT_ATTRIBUTE_H_
#define _TO_CORE_MOVEMENT_ATTRIBUTE_H_

#include "../to_attribute.h"

#include "to_position_attribute.h"

#define WALK_DISTANCE 1

typedef struct MovementUse {
    long long xCord;
    long long yCord;
} MovementUse;

EffectResult* _to_movement_attribute_callback(EffectContext* context, EffectUse* use);
Attribute* to_create_movement_attribute();

#endif