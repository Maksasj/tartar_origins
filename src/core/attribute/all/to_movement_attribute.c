#include "to_movement_attribute.h"

// Todo add validation if can stay in tile or something
EffectResult* _to_movement_attribute_callback(EffectContext* context, void* buffer, unsigned long long length) {
    if(strcmp(buffer, "go") != 0)
        return NULL;

    long long newXCord = *(long long*)(buffer + 3);
    long long newYCord = *(long long*)(buffer + 3 + sizeof(long long));

    long long xCord;
    long long yCord;
    if(!_to_get_position(context->domain, &xCord, &yCord))
        return NULL;

    long long xDelta = abs(xCord - newXCord);
    long long yDelta = abs(yCord - newYCord);

    if((xDelta > WALK_DISTANCE) || yDelta > WALK_DISTANCE)
        return NULL;

    _to_set_position(context->domain, newXCord, newYCord);

    printf("Poggers !\n");

    return NULL;
}

Attribute* to_create_movement_attribute() {
    return to_create_effect_attribute("Movement", _to_movement_attribute_callback);
}

