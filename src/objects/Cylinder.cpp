#include "Cylinder.h"


Cylinder::Cylinder(const Vector3 &origin, double radius, double topZ, double bottomZ, Material material)
        : origin(origin), radius(radius), topZ(topZ), bottomZ(bottomZ) {
    this->material = material;
}

double Cylinder::intersectsRayAt(Ray &ray) {
    // (x-u)**2 + (y-v)**2 = r**2; any z between topZ and bottomZ
    // (O_x+D_x*t-u)**2 + (O_y+D_y*t-v)**2 = r**2;
    // P=O+D*t

    double D_x = ray.direction.x;
    double D_y = ray.direction.y;
    double O_x = ray.origin.x;
    double O_y = ray.origin.y;

    double a=1;
    double b=0;
    double c=0;
    double d=0;
    double e=1;
    double f=0;
    double g=0;
    double h=0;
    double i=1;

    double discriminant = pow(-2 * D_x * O_x + 2 * D_x * origin.x - 2 * D_y * O_y + 2 * D_y * origin.y, 2) -
                          4 * (-D_x * D_x - D_y * D_y) *
                          (-O_x * O_x + 2 * O_x * origin.x - O_y * O_y + 2 * O_y * origin.y + radius * radius -
                           origin.x * origin.x - origin.y * origin.y);
    if (discriminant < 0) return -1;
    double i1 = (-sqrt(discriminant) + 2 * D_x * O_x - 2 * D_x * origin.x + 2 * D_y * O_y - 2 * D_y * origin.y) /
                (2 * (-D_x * D_x - D_y * D_y));
    double i2 = (sqrt(discriminant) + 2 * D_x * O_x - 2 * D_x * origin.x + 2 * D_y * O_y - 2 * D_y * origin.y) /
                (2 * (-D_x * D_x - D_y * D_y));

    Vector3 ipoint1 = ray.direction * i1 + ray.origin;
    Vector3 ipoint2 = ray.direction * i2 + ray.origin;

    if (i1 >= 0 && (i2 < 0 || i2 > i1 || !isGoodZ(ipoint2.z) || ray.direction * getNormalVector(ipoint2) > 0)) {
        // csak az 1. lehet jó
        return (isGoodZ(ipoint1.z) && ray.direction * getNormalVector(ipoint1) <= 0) ? i1 : -1;
    } else if (i2 >= 0 && (i1 < 0 || i1 > i2 || !isGoodZ(ipoint1.z) || ray.direction * getNormalVector(ipoint1) > 0)) {
        // csak az 2. lehet jó
        return (isGoodZ(ipoint2.z) && ray.direction * getNormalVector(ipoint2) <= 0) ? i2 : -1;
    } else {
        return -1;
    }
}


bool Cylinder::isGoodZ(double z) const {
    return (z <= topZ + origin.z) && (z >= bottomZ + origin.z);
}

Vector3 Cylinder::getNormalVector(Vector3 &intersectionPoint) {
    auto n = Vector3::fromTo(origin, intersectionPoint);
    n.z = 0;
    return n._normalize();
}
