//
// Created by ambru on 2022. 01. 24..
//

#include "Cylinder.h"
#include "CylinderInsideOut.h"

Vector3 CylinderInsideOut::getNormalVector(Vector3 &intersectionPoint) {
    auto n = Vector3::fromTo(origin, intersectionPoint);
    n.z = 0;
    n.x *= -1;
    n.y *= -1;
    return n._normalize();
}

double CylinderInsideOut::intersectsRayAt(Ray &ray) {
    return Cylinder::intersectsRayAt(ray);
}

CylinderInsideOut::CylinderInsideOut(const Vector3 &origin, double radius, double topZ, double bottomZ,
                                     const Material &material) : Cylinder(origin, radius, topZ, bottomZ, material) {}

