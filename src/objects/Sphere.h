#pragma once

#include <HittableObject.h>
#include <Vector3.h>

class Sphere : public HittableObject {
public:
    Vector3 origin;

    double radius;
    Sphere(const Vector3 &origin, double radius, Color color);

    double intersectsRayAt(Ray &ray) override;
};


