#include "to_movement_attribute.h"

EffectResult* _to_movement_attribute_callback(Attribute* effect, Attribute* domain, Attribute* target, void* buffer, unsigned long long length) {
    return NULL;
}

Attribute* to_create_movement_attribute() {
    return to_create_effect_attribute("Movement", _to_movement_attribute_callback);
}

