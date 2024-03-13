#include "to_slashing_attribute.h"

#include "to_world.h"

EffectResult* _to_slashing_attribute_callback(EffectContext* context, EffectUse* use) {
    if(!to_is_effect_use_id(use, "slashing"))
        return NULL;

    SlashingUse m;
    memcpy(&m, use->buffer, sizeof(m));

    long long xCord;
    long long yCord;
    if(!_to_get_position(context->initiator, &xCord, &yCord))
        return NULL;

    long long xDelta = abs(xCord - m.xCord);
    long long yDelta = abs(yCord - m.yCord);

    if((xDelta > SLASHING_DISTANCE) || yDelta > SLASHING_DISTANCE)
        return NULL;

    long long strength = to_value_accumulate(context->initiator, "Strength");

    for(int i = 0; i < TO_WORLD_MAX_CREATURES; ++i) {
        Attribute* creature = context->world->creatures[i];

        if(creature == NULL)
            continue;

        long long xCreature;
        long long yCreature;
        if(!_to_get_position(creature, &xCreature, &yCreature))
            continue;

        if(xCreature != m.xCord || yCreature != m.yCord)
            continue;

        Attribute* health = to_set_find_attribute_name(creature, "Health");

        if(health != NULL) {
            health->value.value -= strength;

            if(health->value.value <= 0) {
                to_set_remove_attribute_name(creature, "Health");
                to_set_append_attribute(creature, to_create_tag_attribute("Dead"));
                to_attribute_stringify(creature);
            }
        }
    }

    return NULL;
}

Attribute* to_create_slashing_attribute() {
    return to_create_effect_attribute("Slashing", _to_slashing_attribute_callback);
}

