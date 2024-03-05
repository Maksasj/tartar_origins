#ifndef _TO_CORE_ENTITY_H_
#define _TO_CORE_ENTITY_H_

#include <stdlib.h>
#include <stdio.h>

#include "attribute/to_attribute.h"

typedef struct Entity {
    unsigned int attributeCount;
    Attribute* attributes[16];

    long long xPos;
    long long yPos;
} Entity;

Entity* to_create_entity(long long xPos, long long yPos);

void to_free_entity(Entity* entity);

void to_entity_add_attribute(Entity* entity, Attribute* attribute);

void to_entity_stringify(Entity* entity);

#endif