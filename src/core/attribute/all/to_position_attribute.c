#include "to_position_attribute.h"

Attribute* to_create_position_attribute(long long xCord, long long yCord) {
    Attribute* position = to_create_set_attribute("Position");

    to_set_append_attribute(position, to_create_value_attribute("xCoordinate", xCord));
    to_set_append_attribute(position, to_create_value_attribute("yCoordinate", yCord));

    return position;
}

int _to_get_position(Attribute* domain, long long* xCord, long long* yCord) {
    Attribute* position = to_set_find_attribute_name(domain, "Position");
    if(position == NULL)
        return 0;

    Attribute* xCoordinate = to_set_find_attribute_name(position, "xCoordinate");
    Attribute* yCoordinate = to_set_find_attribute_name(position, "yCoordinate");
    if(xCoordinate == NULL || yCoordinate == NULL)
        return 0;

    if(xCord != NULL)
        *xCord = xCoordinate->value.value;

    if(yCord != NULL)
        *yCord = yCoordinate->value.value;

    return 1;
}

int _to_set_position(Attribute* domain, long long xCord, long long yCord) {
    Attribute* position = to_set_find_attribute_name(domain, "Position");
    if(position == NULL)
        return 0;

    Attribute* xCoordinate = to_set_find_attribute_name(position, "xCoordinate");
    Attribute* yCoordinate = to_set_find_attribute_name(position, "yCoordinate");
    if(xCoordinate == NULL || yCoordinate == NULL)
        return 0;

    xCoordinate->value.value = xCord;
    yCoordinate->value.value = yCord;

    return 1;
}