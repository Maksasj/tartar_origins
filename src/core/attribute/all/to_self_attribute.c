#include "to_self_attribute.h"

EffectResult* _to_self_attribute_callback(Attribute* effect, Attribute* domain, Attribute* target, void* buffer, unsigned long long length)  {
    char argv[16][16];
    memcpy(argv, buffer, sizeof(argv));

    if(strcmp(argv[0], "self") != 0)
        return NULL;

    EffectResult* result = to_create_effect_result();

    to_append_effect_result(result, domain);

    return result;
}

Attribute* to_create_self_attribute() {
    return to_create_effect_attribute("_Self", _to_self_attribute_callback);
}
