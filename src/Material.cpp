//
// Created by ambru on 2021. 12. 09..
//

#include "Material.h"

Material::Material(const Color &_color, const Color &d, const Color &s, const Color &shininess, const Color &reflection)
        : color(_color), d(d), s(s), shininess(shininess), reflection(reflection) {}
