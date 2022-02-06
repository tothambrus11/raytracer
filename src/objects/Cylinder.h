#pragma once

#include "HittableObject.h"
#include "gmtl/Matrix.h"

using namespace gmtl;

class Cylinder : HittableObject {


    [[nodiscard]] bool isGoodZ(double z) const;

public:
    Cylinder(const Vector3 &origin, double radius,double topZ, double bottomZ, Material material);

    Vector3 getNormalVector(Vector3 &intersectionPoint) override;

    double intersectsRayAt(Ray &ray) override;

    Vector3 origin;

    Matrix33d rotation;
    Matrix33d rotationInverse;

    double topZ;

    void updateRotation(double angle);

    double radius;
    double bottomZ;
};
