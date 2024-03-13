#include "to_stat_attribute.h"

Attribute* to_create_stat_attribute(char name[16], long long initialValue) {
    Attribute* stat = to_create_set_attribute(name);

    to_set_append_attribute(stat, to_create_tag_attribute("Stat"));
    to_set_append_attribute(stat, to_create_value_attribute("Value", initialValue));

    return stat;
}

long long _to_stat_traverse(Attribute* attribute, char name[16]) {
    if(attribute == NULL)
        return 0;

    if(attribute->info.type != SET_ATTRIBUTE)
        return 0;

    if(strcmp(attribute->info.name, name) != 0) {
        long long value = 0;

        for(int i = 0; i < TO_SET_ATTRIBUTE_MAX_CHILDS; ++i)
            if(attribute->set.attributes[i] != NULL)
                value += _to_stat_traverse(attribute->set.attributes[i], name);

        return value;
    }

    if(to_set_find_attribute_name(attribute, "Stat") == NULL)
        return 0;

    Attribute* value = to_set_find_attribute_name(attribute, "Value");
    if(value != NULL && value->info.type == VALUE_ATTRIBUTE)
        return value->value.value;

    return 0;
}
