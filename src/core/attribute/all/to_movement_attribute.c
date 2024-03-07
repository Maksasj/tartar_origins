#include "to_movement_attribute.h"

// Todo add validation if can stay in tile or something
EffectResult* _to_movement_attribute_callback(EffectContext* context, void* buffer, unsigned long long length) {
    if(strcmp(buffer, "go") != 0)
        return NULL;

    long long newXCord = *(long long*)(buffer + 3);
    long long newYCord = *(long long*)(buffer + 3 + sizeof(long long));

    Attribute* position = to_set_find_attribute_name(context->domain, "Position");
    if(position == NULL)
        return NULL;

    Attribute* xCoordinate = to_set_find_attribute_name(position, "xCoordinate");
    Attribute* yCoordinate = to_set_find_attribute_name(position, "yCoordinate");
    if(xCoordinate == NULL || yCoordinate == NULL)
        return NULL;

    long long xCord = xCoordinate->value.value;
    long long yCord = yCoordinate->value.value;

    signed long long xDelta = abs(xCord - newXCord);
    signed long long yDelta = abs(yCord - newYCord);

    const signed long long walkDistance = 1;

    if((xDelta > walkDistance) || yDelta > walkDistance)
        return NULL;

    xCoordinate->value.value = newXCord;
    yCoordinate->value.value = newYCord;

    return NULL;
}

Attribute* to_create_movement_attribute() {
    return to_create_effect_attribute("Movement", _to_movement_attribute_callback);
}

