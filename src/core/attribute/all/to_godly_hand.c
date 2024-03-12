#include "to_godly_hand.h"

// Todo add validation if can stay in tile or something
EffectResult* _to_godly_hand_attribute_callback(EffectContext* context, EffectUse* use) {
    if(!to_is_effect_use_id(use, "ghand"))
        return NULL;

    GodlyHandUse ghand;
    memcpy(&ghand, use->buffer, sizeof(ghand));

    // Todo maybe check if valid material
    to_world_set_tile(context->world, ghand.xCord, ghand.yCord, ghand.material);

    return NULL;
}

Attribute* to_create_godly_hand_attribute() {
    return to_create_effect_attribute("Godly Hand", _to_godly_hand_attribute_callback);
}

