//
// Created by ambru on 2021. 12. 09..
//

#pragma once

#include "array"
#include "color.h"

using namespace std;

class Material {
public:
    Color color; // color of the object
    Color d; // diffuse reflection constant
    Color s; // specular reflection constant
    Color shininess;
    Color reflection;

    Material(const Color &_color, const Color &d, const Color &s, const Color &shininess, const Color &reflection);

    Material() = default;
};
