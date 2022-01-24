#pragma once

#include "HittableObject.h"

class Cylinder : HittableObject {
    double bottomZ;

    double radius;


    [[nodiscard]] bool isGoodZ(double z) const;

public:
    Cylinder(const Vector3 &origin, double radius,double topZ, double bottomZ, Material material);

    Vector3 getNormalVector(Vector3 &intersectionPoint) override;

    double intersectsRayAt(Ray &ray) override;

    Vector3 origin;
    double topZ;
};
