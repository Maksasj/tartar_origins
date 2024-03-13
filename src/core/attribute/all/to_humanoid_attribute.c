#include "to_humanoid_attribute.h"

Attribute* to_create_humanoid_attribute() {
    Attribute* humanoid = to_create_set_attribute("Humanoid");

    to_set_append_attribute(humanoid, to_create_movement_attribute());
    to_set_append_attribute(humanoid, to_create_vision_attribute());

    return humanoid;
}

