#pragma once

#include <HittableObject.h>

class Octahedron : public HittableObject {
public:
    Vector3 origin;

    Octahedron(const Vector3 &origin, const Color &color, double size);

    double size;

    double intersectsRayAt(Ray &ray) override;

    Color calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                vector<HittableObject *> &objects, vector<PointLight *> &lights) override;
};
