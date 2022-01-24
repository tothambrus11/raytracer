#pragma once

#include "HittableObject.h"
#include "Cylinder.h"

class CylinderInsideOut : public Cylinder {

public:
    CylinderInsideOut(const Vector3 &origin, double radius, double topZ, double bottomZ, const Material &material);

    Vector3 getNormalVector(Vector3 &intersectionPoint) override;

    double intersectsRayAt(Ray &ray) override;
};
