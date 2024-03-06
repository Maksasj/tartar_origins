#include "to_vision_attribute.h"

EffectResult* _to_vision_attribute_callback(Attribute* effect, Attribute* domain, Attribute* target, void* buffer, unsigned long long length) {
    return NULL;
}

Attribute* to_create_vision_attribute() {
    return to_create_effect_attribute("Vision", _to_vision_attribute_callback);
}
