#include "to_vision_attribute.h"
#include "to_world.h"

EffectResult* _to_vision_attribute_callback(EffectContext* context, void* buffer, unsigned long long length) {
    char argv[16][16];
    memcpy(argv, buffer, sizeof(argv));

    if(strcmp(argv[0], "vision") != 0)
        return NULL;

    long long xCord;
    long long yCord;
    if(!_to_get_position(context->domain, &xCord, &yCord))
        return NULL;

    EffectResult* result = to_create_effect_result();

    // First lets add all creatures
    // Todo check this part
    for(int i = 0; i < 1024; ++i) {
        Attribute* creature = context->world->creatures[i];

        if(creature == NULL)
            continue;

        long long yCordCreature;
        long long xCordCreature;
        if(!_to_get_position(creature, &xCordCreature, &yCordCreature))
            continue;

        long long xDelta = abs(xCord - xCordCreature);
        long long yDelta = abs(yCord - yCordCreature);

        if(xDelta > VISION_DISTANCE || yDelta > VISION_DISTANCE)
            continue;

        to_append_effect_result(result, creature);
    }

    for(int x = -VISION_DISTANCE; x < VISION_DISTANCE; ++x) {
        for(int y = -VISION_DISTANCE; y < VISION_DISTANCE; ++y) {
            long long tileXCord = xCord + x;
            long long tileYCord = yCord + y;

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
