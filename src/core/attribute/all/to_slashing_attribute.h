#ifndef _TO_CORE_SLASHING_ATTRIBUTE_H_
#define _TO_CORE_SLASHING_ATTRIBUTE_H_

#include "../to_attribute.h"

#include "to_position_attribute.h"

#define SLASHING_DISTANCE 1

typedef struct SlashingUse {
    long long xCord;
    long long yCord;
} SlashingUse;

EffectResult* _to_slashing_attribute_callback(EffectContext* context, EffectUse* use);
Attribute* to_create_slashing_attribute();

#endif