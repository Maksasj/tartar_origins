#include "to_effect_result.h"

EffectResult* to_create_effect_result() {
    EffectResult* result = malloc(sizeof(EffectResult));

    result->count = 0;
    result->attributes = NULL;

    return result;
}

void to_append_effect_result(EffectResult* result, union Attribute* attributes) {
    if(result->attributes == NULL)
        result->attributes = malloc(sizeof(union Attribute*));
    else
        result->attributes = realloc(result->attributes, (result->count + 1) * sizeof(union Attribute*)); // Todo fix realloc

    result->attributes[result->count] = attributes;
    ++result->count;
}

void to_free_effect_result(EffectResult* result) {
    free(result->attributes);
    free(result);
}
