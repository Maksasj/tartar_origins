#include "to_material_attribute.h"

int _to_has_material(Attribute* domain, const char* material) {
    if(domain->info.type != SET_ATTRIBUTE)
        return 0;

    Attribute* attribute = to_set_find_attribute_name(domain, "Material");
    if(attribute == NULL)
        return 0;

    Attribute* mat = to_set_find_attribute_name(attribute, material);
    if(mat == NULL)
        return 0;

    return 1;
}

Attribute* to_create_material_attribute(const char* material) {
    Attribute* mat = to_create_set_attribute("Material");

    to_set_append_attribute(mat, to_create_tag_attribute(material));

    return mat;
}

Attribute* to_create_materials_attribute(const char* materials[], unsigned int count) {
    Attribute* mat = to_create_set_attribute("Material");

    for(int i = 0; i < count; ++i)
        to_set_append_attribute(mat, to_create_tag_attribute(materials[i]));

    return mat;
}
