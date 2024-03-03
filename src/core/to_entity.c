#include "to_entity.h"

Entity* to_create_entity(long long xPos, long long yPos) {
    Entity* entity = malloc(sizeof(Entity));

    for(int i = 0; i < 16; ++i)
        entity->attributes[i] = NULL;

    entity->xPos = xPos;
    entity->yPos = yPos;
    entity->attributeCount = 0;

    return entity;
}

void to_free_entity(Entity* entity) {
    for(int i = 0; i < 16; ++i) {
        Attribute* attribute = entity->attributes[i];

        if(attribute == NULL)
            to_free_attribute(attribute);
    }

    free(entity);
}

void to_entity_add_attribute(Entity* entity, Attribute* attribute) {
    /*
    for(int i = 0; i < 16; ++i) {
        if(entity->attributes[i] == NULL) {
            entity->attributes[i] = attribute;
            break;
        }
    }
    */

    // Todo
    entity->attributes[entity->attributeCount] = attribute;
    ++entity->attributeCount;
}

void to_entity_stringify(Entity* entity) {
    printf("Entity: \n");
    for(int i = 0; i < 16; ++i) {
        if(entity->attributes[i] != NULL) {
            if(entity->attributes[i]->info.type == TAG_ATTRIBUTE) {
                printf("    Tag: [%s]\n", entity->attributes[i]->info.name);
            } else if(entity->attributes[i]->info.type == EFFECT_ATTRIBUTE) {
                printf("    Effect: [%s]\n", entity->attributes[i]->info.name);
            }
        } else {
            break;
        }
    }
}
