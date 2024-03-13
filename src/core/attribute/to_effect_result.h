#ifndef _TO_CORE_EFFECT_RESULT_H_
#define _TO_CORE_EFFECT_RESULT_H_

#include <stdlib.h>

struct EffectUse;
struct World;
struct Effect;
union Attribute;

#define TO_SERVER_MAX_PLAYERS 256

typedef struct EffectContext {
    union Attribute* effect;
    union Attribute* initiator;
    union Attribute* domain;
    union Attribute* target;
    struct World* world;
} EffectContext;

typedef struct EffectResult {
    unsigned int count;
    union Attribute** attributes;
} EffectResult;
typedef EffectResult* (EffectCallback)(struct EffectContext* context, struct EffectUse* use);

EffectResult* to_create_effect_result();
void to_append_effect_result(EffectResult* result, union Attribute* attributes);
void to_free_effect_result(EffectResult* result);

#endif