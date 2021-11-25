//
// Created by ambru on 2021. 11. 25..
//

#pragma once

#include <HittableObject.h>

class Octahedron : HittableObject {
public:
    Vector3 origin;

    double size;
    Octahedron(const Vector3 &origin, double size);

    double intersectsRayAt(Ray &ray) override;
};


