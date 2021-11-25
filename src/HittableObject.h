#pragma once

#include <Ray.h>
#include <color.h>

class HittableObject {
public:
    Color color;
    virtual double intersectsRayAt(Ray& ray) = 0;
};


