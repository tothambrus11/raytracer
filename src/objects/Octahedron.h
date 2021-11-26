#pragma once

#include <HittableObject.h>

class Octahedron : public HittableObject {
public:
    Vector3 origin;

    Octahedron(const Vector3 &origin, const Color &color, double size);

    double size;

    double intersectsRayAt(Ray &ray) override;
};


