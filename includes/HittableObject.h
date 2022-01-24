#pragma once

#include <Ray.h>
#include <color.h>
#include <vector>
#include "Material.h"
#include "PointLight.h"
#include "SDL2/SDL.h"

class HittableObject {
public:
    Material material;

    HittableObject() = default;

    virtual double intersectsRayAt(Ray &ray) = 0;

    Color calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                        vector<HittableObject *> &objects, vector<PointLight *> &lights);
    virtual Vector3 getNormalVector(Vector3 &intersectionPoint) = 0;
};


