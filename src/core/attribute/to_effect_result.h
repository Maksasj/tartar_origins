#ifndef _TO_CORE_EFFECT_RESULT_H_
#define _TO_CORE_EFFECT_RESULT_H_

#include <stdlib.h>

struct Effect;
union Attribute;

typedef struct EffectResult {
    unsigned int count;
    union Attribute** attributes;
} EffectResult;
typedef EffectResult* (EffectCallback)(union Attribute* effect, union Attribute* domain, union Attribute* target, void* buffer, unsigned long long length);

EffectResult* to_create_effect_result();
void to_append_effect_result(EffectResult* result, union Attribute* attributes);
void to_free_effect_result(EffectResult* result);

#endif