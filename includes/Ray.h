#pragma once
#include "Vector3.h"

class Ray {
public:
    Ray();

    Vector3 origin;
    Vector3 direction;

    Ray(const Vector3 &origin, const Vector3 &direction);
};


