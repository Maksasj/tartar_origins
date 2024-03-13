#include "to_attribute.h"

#include <stdio.h>

long long to_value_accumulate(union Attribute* attribute, const char name[16]) {
    if(attribute == NULL)
        return 0;

    if(attribute->info.type == VALUE_ATTRIBUTE) {
        if(strcmp(attribute->info.name, name) == 0)
            return attribute->value.value;
    } else if(attribute->info.type == SET_ATTRIBUTE) {
        long long value = 0;

        for(int i = 0; i < TO_SET_ATTRIBUTE_MAX_CHILDS; ++i) {
            Attribute* at = attribute->set.attributes[i];

            if(at != NULL)
                value += to_value_accumulate(at, name);
        }

        return value;
    }

    return 0;
}

int to_is_effect_use_id(EffectUse* use, const char id[16]) {
    if(use == NULL)
        return 0;

    if(strcmp(use->id, id) == 0)
        return 1;

    return 0;
}

Attribute* to_create_tag_attribute(const char* name) {
    if(name == NULL)
        return NULL;

    unsigned int length = strlen(name);

    if(length >= 16)
        return NULL;

    Attribute* attribute = malloc(sizeof(Attribute));

    strcpy(attribute->info.name, name);
    attribute->info.type = TAG_ATTRIBUTE;

    return attribute;
}

Attribute* to_create_value_attribute(const char* name, unsigned long long value) {
    if(name == NULL)
        return NULL;

    unsigned int length = strlen(name);

    if(length >= 16)
        return NULL;

    Attribute* attribute = malloc(sizeof(Attribute));

    strcpy(attribute->info.name, name);
    attribute->info.type = VALUE_ATTRIBUTE;

    attribute->value.value = value;

    return attribute;
}

Attribute* to_create_effect_attribute(const char* name, EffectCallback* effect) {
    if(name == NULL)
        return NULL;

    unsigned int length = strlen(name);

    if(length >= 16)
        return NULL;

    Attribute* attribute = malloc(sizeof(Attribute));

    strcpy(attribute->info.name, name);
    attribute->info.type = EFFECT_ATTRIBUTE;

    attribute->effect.effect = effect;

    return attribute;
}

Attribute* to_create_set_attribute(const char* name) {
    if(name == NULL)
        return NULL;

    unsigned int length = strlen(name);

    if(length >= 16)
        return NULL;

    Attribute* attribute = malloc(sizeof(Attribute));

    strcpy(attribute->info.name, name);
    attribute->info.type = SET_ATTRIBUTE;
    memset(attribute->set.attributes, 0, 16 * sizeof(Attribute*));

    return attribute;
}

Attribute* to_set_append_attribute(Attribute* set, Attribute* attribute) {
    for(int i = 0; i < TO_SET_ATTRIBUTE_MAX_CHILDS; ++i) {
        Attribute* at = set->set.attributes[i];

        if(at != NULL)
            continue;

        set->set.attributes[i] = attribute;

        return attribute;
    }

    return NULL;
}

Attribute* to_set_find_attribute_name(Attribute* attribute, const char* name) {
    if(attribute == NULL)
        return NULL;

    if(attribute->info.type != SET_ATTRIBUTE)
        return NULL;

    for(int i = 0; i < TO_SET_ATTRIBUTE_MAX_CHILDS; ++i) {
        Attribute* at = attribute->set.attributes[i];

        if(at == NULL)
            continue;

        if(strcmp(at->info.name, name) == 0)
            return at;
    }

    return NULL;
}

int to_set_remove_attribute_name(Attribute* attribute, const char* name) {
    for(int i = 0; i < TO_SET_ATTRIBUTE_MAX_CHILDS; ++i) {
        Attribute* at = attribute->set.attributes[i];

        if(at == NULL)
            continue;

        if(strcmp(at->info.name, name) != 0)
            continue;

        to_free_attribute(attribute->set.attributes[i]);
        attribute->set.attributes[i] = NULL;
    }

    return 0;
}

void _to_stringify_attribute(Attribute* attribute, int depth) {
    if(attribute == NULL);

    for(int i = 0; i < depth; ++i)
        printf("    ");

    AttributeType type = attribute->info.type;

    if(type == TAG_ATTRIBUTE) {
        printf("Tag: [%s]\n", attribute->info.name);
    } else if(type == EFFECT_ATTRIBUTE) {
        printf("Effect: [%s]\n", attribute->info.name);
    } else if(type == VALUE_ATTRIBUTE) {
        printf("Value: [%s] [%lld]\n", attribute->info.name, attribute->value.value);
    } else if(type == SET_ATTRIBUTE) {
        printf("Set: [%s]\n", attribute->info.name);

        for(int i = 0; i < TO_SET_ATTRIBUTE_MAX_CHILDS; ++i)
            if(attribute->set.attributes[i] != NULL)
                _to_stringify_attribute(attribute->set.attributes[i], depth + 1);
    }
}

void to_attribute_stringify(Attribute* attribute) {
    _to_stringify_attribute(attribute, 0);
}

void to_free_attribute(Attribute* attribute) {
    if(attribute == NULL)
        return;

    if(attribute->info.type == TAG_ATTRIBUTE) {
        // Todo
    } else if(attribute->info.type == VALUE_ATTRIBUTE) {
        // Todo
    } else if(attribute->info.type == EFFECT_ATTRIBUTE) {
        // Todo
    } else if(attribute->info.type == SET_ATTRIBUTE) {
        for(int i = 0; i < 16; ++i)
            if(attribute->set.attributes[i] != NULL)
                to_free_attribute(attribute->set.attributes[i]);
    }

    free(attribute);
}
