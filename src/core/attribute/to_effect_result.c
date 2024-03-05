#include "to_effect_result.h"

EffectResult* to_create_effect_result() {
    EffectResult* result = malloc(sizeof(EffectResult));

    result->count = 0;
    result->entities = NULL;

    return result;
}

void to_append_effect_result(EffectResult* result, struct Entity* entity) {
    if(result->entities == NULL)
        result->entities = malloc(sizeof(struct Entity*));
    else
        result->entities = realloc(result->entities, (result->count + 1) * sizeof(struct Entity*)); // Todo fix realloc

    result->entities[result->count] = entity;
    ++result->count;
}

void to_free_effect_result(EffectResult* result) {
    free(result->entities);
    free(result);
}
