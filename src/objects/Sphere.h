#pragma once

#include <HittableObject.h>
#include <Vector3.h>
#include <vector>
#include "Material.h"

class Sphere : public HittableObject {
public:
    Vector3 origin;

    double radius;
    Sphere(const Vector3 &origin, double radius, Color c, Material material);

    double intersectsRayAt(Ray &ray) override;

    Color calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                vector<HittableObject *> &objects, vector<PointLight *> &lights) override;
};


