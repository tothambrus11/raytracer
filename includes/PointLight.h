//
// Created by ambru on 2021. 12. 09..
//

#pragma once
#include "Vector3.h"
#include "color.h"

class PointLight {
public:
    Vector3 origin;
    Color color;

    PointLight(const Vector3 &origin, const Color &color);
};


