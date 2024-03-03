#ifndef _TO_CORE_ATTRIBUTE_H_
#define _TO_CORE_ATTRIBUTE_H_

#include <stdlib.h>
#include <string.h>

typedef enum AttributeType {
    TAG_ATTRIBUTE,
    VALUE_ATTRIBUTE,
    EFFECT_ATTRIBUTE
} AttributeType;

typedef struct AttributeInfo {
    AttributeType type;

    char name[16];

    unsigned int class;
    unsigned int variation;
} AttributeInfo;

typedef struct Tag {
    AttributeInfo info;
} Tag;

typedef struct Value {
    AttributeInfo info;

    unsigned long long value;
    unsigned long long maxValue;
} Value;

struct Effect;
struct Entity;
union Attribute;
typedef void (EffectCallback)(union Attribute* effect, struct Entity* domain, struct Entity* target, unsigned int argc, char argv[16][16]);

typedef struct Effect {
    AttributeInfo info;
    EffectCallback* effect;
} Effect;

typedef union Attribute {
    AttributeInfo info;

    Tag tag;
    Value value;
    Effect effect;
} Attribute;

Attribute* to_create_tag_attribute(char* name);
Attribute* to_create_effect_attribute(char* name, EffectCallback* effect);

void to_free_attribute(Attribute* attribute);

#endif