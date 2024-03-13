#include "to_vision_attribute.h"
#include "to_world.h"

EffectResult* _to_vision_attribute_callback(EffectContext* context, EffectUse* use) {
    if(!to_is_effect_use_id(use, "vision"))
        return NULL;

    long long xCord;
    long long yCord;
    if(!_to_get_position(context->domain, &xCord, &yCord))
        return NULL;

    EffectResult* result = to_create_effect_result();

    for(int x = -VISION_DISTANCE; x < VISION_DISTANCE; ++x) {
        for(int y = -VISION_DISTANCE; y < VISION_DISTANCE; ++y) {
            long long tileXCord = xCord + x;
            long long tileYCord = yCord + y;

            Attribute* tile = to_world_get_tile(context->world, tileXCord, tileYCord);

            if(tile != NULL) {
                double distanceSqr = x*x + y*y;

                if(distanceSqr > VISION_DISTANCE * VISION_DISTANCE)
                    continue;

                to_append_effect_result(result, tile);
            }
        }
    }

    // Todo check this part
    for(int i = 0; i < TO_WORLD_MAX_CREATURES; ++i) {
        Attribute* creature = context->world->creatures[i];

        if(creature == NULL)
            continue;

        long long yCordCreature;
        long long xCordCreature;
        if(!_to_get_position(creature, &xCordCreature, &yCordCreature))
            continue;

        double x = (double) xCord - (double) xCordCreature;
        double y = (double) yCord - (double) yCordCreature;
        double distanceSqr = x*x + y*y;

        if(distanceSqr > VISION_DISTANCE * VISION_DISTANCE)
            continue;

        to_append_effect_result(result, creature);
    }

    for(int i = 0; i < TO_SERVER_MAX_PLAYERS; ++i)
        if(context->players[i] != NULL)
            to_append_effect_result(result, context->players[i]);

    return result;
}

Attribute* to_create_vision_attribute() {
    return to_create_effect_attribute("Vision", _to_vision_attribute_callback);
}
