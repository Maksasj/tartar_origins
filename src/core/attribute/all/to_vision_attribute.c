#include "to_vision_attribute.h"
#include "to_world.h"

int _to_has_position(Attribute* attribute) {
    Attribute* position = to_set_find_attribute_name(attribute, "Position");
    if(position == NULL)
        return 0;

    Attribute* xCoordinate = to_set_find_attribute_name(position, "xCoordinate");
    Attribute* yCoordinate = to_set_find_attribute_name(position, "yCoordinate");
    if(xCoordinate == NULL || yCoordinate == NULL)
        return 0;

    return 1;
}

EffectResult* _to_vision_attribute_callback(EffectContext* context, void* buffer, unsigned long long length) {
    char argv[16][16];
    memcpy(argv, buffer, sizeof(argv));

    if(strcmp(argv[0], "vision") != 0)
        return NULL;

    if(!_to_has_position(context->domain))
        return NULL;

    Attribute* position = to_set_find_attribute_name(context->domain, "Position");
    Attribute* xCoordinate = to_set_find_attribute_name(position, "xCoordinate");
    Attribute* yCoordinate = to_set_find_attribute_name(position, "yCoordinate");

    signed long long xCord = xCoordinate->value.value;
    signed long long yCord = yCoordinate->value.value;

    EffectResult* result = to_create_effect_result();

    // First lets add all creatures
    // Todo check this part
    for(int i = 0; i < 1024; ++i) {
        Attribute* creature = context->world->creatures[i];

        if(creature == NULL)
            continue;

        if(!_to_has_position(context->domain))
            continue;

        Attribute* positionCreature = to_set_find_attribute_name(creature, "Position");
        Attribute* xCoordinateCreature = to_set_find_attribute_name(positionCreature, "xCoordinate");
        Attribute* yCoordinateCreature = to_set_find_attribute_name(positionCreature, "yCoordinate");

        long long xCordCreature = xCoordinateCreature->value.value;
        long long yCordCreature = yCoordinateCreature->value.value;

        long long xDelta = abs(xCord - xCordCreature);
        long long yDelta = abs(yCord - yCordCreature);

        if(xDelta > VISION_DISTANCE)
            continue;

        if(yDelta > VISION_DISTANCE)
            continue;

        to_append_effect_result(result, creature);
    }

    for(int x = -VISION_DISTANCE; x < VISION_DISTANCE; ++x) {
        for(int y = -VISION_DISTANCE; y < VISION_DISTANCE; ++y) {
            signed long long tileXCord = xCord + x;
            signed long long tileYCord = yCord + y;

            Attribute* tile = to_world_get_tile(context->world, tileXCord, tileYCord);

            if(tile != NULL)
                to_append_effect_result(result, tile);
        }
    }

    return result;
}

Attribute* to_create_vision_attribute() {
    return to_create_effect_attribute("Vision", _to_vision_attribute_callback);
}
