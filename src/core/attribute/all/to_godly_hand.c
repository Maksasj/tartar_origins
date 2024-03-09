#include "to_godly_hand.h"

// Todo add validation if can stay in tile or something
EffectResult* _to_godly_hand_attribute_callback(EffectContext* context, void* buffer, unsigned long long length) {
    if(strcmp(buffer, "ghand") != 0)
        return NULL;

    long long newXCord = *(long long*)(buffer + 6 + 16);
    long long newYCord = *(long long*)(buffer + 6 + 16 + sizeof(long long));

    char material[16];
    memcpy(material, buffer + 6, 16);

    // Todo maybe check if valid material
    to_world_set_tile(context->world, newXCord, newYCord, material);

    return NULL;
}

Attribute* to_create_godly_hand_attribute() {
    return to_create_effect_attribute("Godly hand", _to_godly_hand_attribute_callback);
}

