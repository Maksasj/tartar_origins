#ifndef _TO_CORE_EFFECT_RESULT_H_
#define _TO_CORE_EFFECT_RESULT_H_

#include <stdlib.h>

struct Effect;
struct Entity;
union Attribute;

typedef struct EffectResult {
    unsigned int count;
    struct Entity** entities;
} EffectResult;
typedef EffectResult* (EffectCallback)(union Attribute* effect, struct Entity* domain, struct Entity* target, unsigned int argc, char argv[16][16]);

EffectResult* to_create_effect_result();
void to_append_effect_result(EffectResult* result, struct Entity* entity);
void to_free_effect_result(EffectResult* result);

#endif