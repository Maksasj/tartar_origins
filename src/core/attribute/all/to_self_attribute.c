#include "to_self_attribute.h"

EffectResult* _to_self_attribute_callback(EffectContext* context, EffectUse* use)  {
    if(!to_is_effect_use_id(use, "self"))
        return NULL;

    EffectResult* result = to_create_effect_result();

    to_append_effect_result(result, context->domain);

    return result;
}

Attribute* to_create_self_attribute() {
    return to_create_effect_attribute("_Self", _to_self_attribute_callback);
}
