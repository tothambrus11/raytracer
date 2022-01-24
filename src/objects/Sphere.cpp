//
// Created by ambru on 2021. 11. 23..
//

#include <Ray.h>
#include <PointLight.h>
#include "Sphere.h"
#include "iostream"

using namespace std;

Sphere::Sphere(const Vector3 &origin, double radius, Material material)
        : origin(origin), radius(radius) {
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

Vector3 Sphere::getNormalVector(Vector3 &intersectionPoint) {
    return Vector3::fromTo(origin, intersectionPoint)._normalize();
}

