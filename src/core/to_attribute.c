#include "to_attribute.h"

Attribute* to_create_tag_attribute(char* name) {
    if(name == NULL)
        return NULL;

    unsigned int length = strlen(name);

    if(length >= 16)
        return NULL;

    Attribute* attribute = malloc(sizeof(Attribute));

    strcpy(attribute->info.name, name);
    attribute->info.type = TAG_ATTRIBUTE;
    attribute->info.class = 0;
    attribute->info.variation = 0;

    return attribute;
}

Attribute* to_create_effect_attribute(char* name, EffectCallback* effect) {
    if(name == NULL)
        return NULL;

    unsigned int length = strlen(name);

    if(length >= 16)
        return NULL;

    Attribute* attribute = malloc(sizeof(Attribute));

    strcpy(attribute->info.name, name);
    attribute->info.type = EFFECT_ATTRIBUTE;
    attribute->info.class = 0;
    attribute->info.variation = 0;

    attribute->effect.effect = effect;

    return attribute;
}


void to_free_attribute(Attribute* attribute) {
    if(attribute == NULL)
        return;

    if(attribute->info.type == TAG_ATTRIBUTE) {

    } else if(attribute->info.type == VALUE_ATTRIBUTE) {

    } else if(attribute->info.type == EFFECT_ATTRIBUTE) {

    }

    free(attribute);
}
