#ifndef _TO_CORE_MATERIAL_ATTRIBUTE_H_
#define _TO_CORE_MATERIAL_ATTRIBUTE_H_

#include "../to_attribute.h"

Attribute* to_create_material_attribute(const char* material);
Attribute* to_create_materials_attribute(const char* materials[], unsigned int count);

int _to_has_material(Attribute* domain, const char* material);

#endif
