//
// Created by ambru on 2021. 11. 23..
//

#include <Ray.h>
#include <PointLight.h>
#include "Sphere.h"

using namespace std;

Sphere::Sphere(const Vector3 &origin, double radius, Color c, Material material)
        : origin(origin), radius(radius) {
    this->color = c;
    this->material = material;
}

double Sphere::intersectsRayAt(Ray &ray) {

    Vector3 originDiff = ray.origin - origin;

    double a = ray.direction.sq();
    double b = originDiff * ray.direction * 2;
    double c = originDiff.sq() - radius * radius;

    double discriminant = (b * b) - 4 * (a * c);
    if (discriminant < 0) return -1;

    double i1 = (-b + sqrt(discriminant)) / (2 * a);
    double i2 = (-b - sqrt(discriminant)) / (2 * a);


    if (i1 < 0) {
        return i2;
    }
    if (i2 < 0) {
        return i1;
    }
    return min(i1, i2);
}

Color Sphere::calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                    vector<HittableObject *> &objects, vector<PointLight *> &lights) {
    if (remainingIterations == 0) {
        return {};
    }

    auto n = (intersectionPoint - origin).normalize();
    auto e = n * ((incomingRay.direction * -1) * n);
    auto D2 = (e * 2) + incomingRay.direction;
    Ray outgoingRay(intersectionPoint, D2);

    Color c;

    // ambient reflection
    c += material.color; // todo multiply with ambient light

    // diffuse reflection
    for (PointLight *&light: lights) {
        // todo check for shadows

       /* bool foundI = false;
        for (auto o : objects) {
            Ray r = Ray(intersectionPoint, light->origin - intersectionPoint);
            if (o != this && o->intersectsRayAt(r) > 0) {
                foundI = true;
                break;
            }
        }
        if (foundI) { break; }*/

        auto L = (light->origin - intersectionPoint).normalize(); // direction to the light source
        auto e2 = n * (L * n);
        if(L * n < 0){
            break;
        }
        auto LReflection = (e2 * 2 - L).normalize();

        c += (material.d * light->color * (L * n)).minZero();

        c += (material.s * pow(LReflection * incomingRay.direction * -1, 16) * light->color).minZero();

    }

    HittableObject *nearestObject = nullptr;
    double minDistance;
    for (auto &object : objects) {
        double distance = object->intersectsRayAt(outgoingRay);
        if (distance >= 0 && (nearestObject == nullptr || distance < minDistance) && object != this) {
            minDistance = distance;
            nearestObject = object;
        }
    }

    if (nearestObject != nullptr) {
        Color noc = nearestObject->calculateEmittedLight(remainingIterations - 1, outgoingRay,
                                                         outgoingRay.direction * minDistance, objects, lights);
        //c += noc * material.reflection;
    }

    return c;
}
