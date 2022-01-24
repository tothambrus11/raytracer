#pragma once

#include "HittableObject.h"

class Cylinder : HittableObject {
    double bottomZ;
    double topZ;

    double radius;


    double intersectsRayAt(Ray &ray) override;

    bool isGoodZ(double z) const;

    Color calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                vector<HittableObject *> &objects, vector<PointLight *> &lights) override;

public:
    Cylinder(const Vector3 &origin, double radius,double topZ, double bottomZ, Color c, Material material);

    Vector3 origin;
};
