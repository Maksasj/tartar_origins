#ifndef _TO_CORE_GODLY_HAND_ATTRIBUTE_H_
#define _TO_CORE_GODLY_HAND_ATTRIBUTE_H_

#include "../to_attribute.h"

#include "to_position_attribute.h"
#include "to_world.h"

typedef struct GodlyHandUse {
    char material[16];
    long long xCord;
    long long yCord;
} GodlyHandUse;

EffectResult* _to_godly_hand_attribute_callback(EffectContext* context, EffectUse* use);
Attribute* to_create_godly_hand_attribute();

#endif