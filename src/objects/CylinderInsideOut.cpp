//
// Created by ambru on 2022. 01. 24..
//

#include "Cylinder.h"
#include "CylinderInsideOut.h"
#include "iostream"

using namespace std;

Vector3 CylinderInsideOut::getNormalVector(Vector3 &intersectionPoint) {
    auto n = Cylinder::getNormalVector(intersectionPoint);
    n = n * -1;
    return n._normalize();
}

double CylinderInsideOut::intersectsRayAt(Ray &ray) {
    return Cylinder::intersectsRayAt(ray);
}

CylinderInsideOut::CylinderInsideOut(const Vector3 &origin, double radius, double topZ, double bottomZ,
                                     const Material &material) : Cylinder(origin, radius, topZ, bottomZ, material) {}

