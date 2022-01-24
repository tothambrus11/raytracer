#pragma once

#include <HittableObject.h>
#include <Vector3.h>
#include <vector>
#include "Material.h"

class Sphere : public HittableObject {
public:
    Vector3 origin;

    double radius;
    Sphere(const Vector3 &origin, double radius, Material material);

    double intersectsRayAt(Ray &ray) override;

    Vector3 getNormalVector(Vector3 &intersectionPoint) override;
};


