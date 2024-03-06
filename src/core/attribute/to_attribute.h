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

    unsigned long long value;
} Value;

typedef struct Effect {
    AttributeInfo info;

    EffectCallback* effect;
} Effect;

typedef struct AttributeSet {
    AttributeInfo info;

    unsigned int count;
    union Attribute* attributes[16];
} AttributeSet;

typedef union Attribute {
    AttributeInfo info;

    Tag tag;
    Value value;
    Effect effect;

    AttributeSet set;
} Attribute;

Attribute* to_create_tag_attribute(char* name);
Attribute* to_create_value_attribute(char* name, unsigned long long value);
Attribute* to_create_effect_attribute(char* name, EffectCallback* effect);
Attribute* to_create_set_attribute(char* name);

void _to_stringify_attribute(Attribute* attribute, int depth);
void to_attribute_stringify(Attribute* attribute);

void to_free_attribute(Attribute* attribute);

#endif