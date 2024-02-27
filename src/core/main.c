#include <stdio.h>

typedef unsigned int u32;

typedef struct Statblock {
    u32 stamina;
    u32 strength;
    u32 intellect;
    u32 armor;
} Statblock;

typedef struct Attribute {} Attribute;

typedef struct Creature {
    unsigned int attributeCount;
    Attribute* attributes;
} Creature;

// typedef struct LifeAttribute {
// } LifeAttribute;
//
// typedef struct PhysicalAttribute {
// } PhysicalAttribute;
