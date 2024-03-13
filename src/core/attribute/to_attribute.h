#ifndef _TO_CORE_ATTRIBUTE_H_
#define _TO_CORE_ATTRIBUTE_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "to_attribute_info.h"
#include "to_effect_result.h"

typedef struct Tag {
    AttributeInfo info;
} Tag;

typedef struct Value {
    AttributeInfo info;

    long long value;
} Value;

typedef struct EffectUse {
    char id[16];

    unsigned long long size;
    void* buffer;
} EffectUse;

int to_is_effect_use_id(EffectUse* use, const char id[16]);

typedef struct Effect {
    AttributeInfo info;

    EffectCallback* effect;
} Effect;

#define TO_SET_ATTRIBUTE_MAX_CHILDS 16

typedef struct AttributeSet {
    AttributeInfo info;
    union Attribute* attributes[TO_SET_ATTRIBUTE_MAX_CHILDS];
} AttributeSet;

typedef union Attribute {
    AttributeInfo info;

    Tag tag;
    Value value;
    Effect effect;

    AttributeSet set;
} Attribute;

Attribute* to_create_tag_attribute(const char* name);
Attribute* to_create_value_attribute(const char* name, unsigned long long value);
Attribute* to_create_effect_attribute(const char* name, EffectCallback* effect);
Attribute* to_create_set_attribute(const char* name);

// Returns 'attribute' if success, NULL if not
Attribute* to_set_append_attribute(Attribute* set, Attribute* attribute);

Attribute* to_set_find_attribute_name(Attribute* attribute, const char* name);
int to_set_remove_attribute_name(Attribute* attribute, const char* name);

void to_attribute_stringify(Attribute* attribute);

void to_free_attribute(Attribute* attribute);

#endif