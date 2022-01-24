#pragma once

#include <Ray.h>
#include <color.h>
#include <vector>
#include "Material.h"
#include "PointLight.h"
#include "SDL2/SDL.h"

class HittableObject {
public:
    Color color;
    Material material;

    HittableObject() = default;

    virtual double intersectsRayAt(Ray &ray) = 0;

    Color calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                        vector<HittableObject *> &objects, vector<PointLight *> &lights) = 0;
    virtual double getNormalVector() = 0;
};


