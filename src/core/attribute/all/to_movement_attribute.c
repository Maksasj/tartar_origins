#include "to_movement_attribute.h"

// Todo add validation if can stay in tile or something
EffectResult* _to_movement_attribute_callback(EffectContext* context, EffectUse* use) {
    if(!to_is_effect_use_id(use, "go"))
        return NULL;

    MovementUse m;
    memcpy(&m, use->buffer, sizeof(m));

    long long xCord;
    long long yCord;
    if(!_to_get_position(context->initiator, &xCord, &yCord))
        return NULL;

    long long xDelta = abs(xCord - m.xCord);
    long long yDelta = abs(yCord - m.yCord);

    if((xDelta > WALK_DISTANCE) || yDelta > WALK_DISTANCE)
        return NULL;

    _to_set_position(context->initiator, m.xCord, m.yCord);

    return NULL;
}

Attribute* to_create_movement_attribute() {
    return to_create_effect_attribute("Movement", _to_movement_attribute_callback);
}

