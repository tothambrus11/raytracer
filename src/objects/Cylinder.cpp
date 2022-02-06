#include "Cylinder.h"
#include "MyMatrixFunctions.h"

Cylinder::Cylinder(const Vector3 &origin, double radius, double topZ, double bottomZ, Material material)
        : origin(origin), radius(radius), topZ(topZ), bottomZ(bottomZ) {
    this->material = material;
}

double Cylinder::intersectsRayAt(Ray &ray) {
    // (x-u)**2 + (y-v)**2 = r**2; any z between topZ and bottomZ
    // (O_x+D_x*t-u)**2 + (O_y+D_y*t-v)**2 = r**2;
    // P=O+D*t

    // (a*(o_x+d_x*i-u)+b*(o_y+d_y*i-v)+c*(o_z+d_z*i-w))^2 + (d*(o_x+d_x*i-u)+e*(o_y+d_y*i-v)+f*(o_z+d_z*i-w))^2 - r*r = 0
    // (a*(o_x+d_x*x-u)+b*(o_y+d_y*x-v)+c*(o_z+d_z*x-w))^2 + (d*(o_x+d_x*x-u)+e*(o_y+d_y*x-v)+f*(o_z+d_z*x-w))^2 - r*r = 0

    double d_x = ray.direction.x;
    double d_y = ray.direction.y;
    double d_z = ray.direction.z;
    double o_x = ray.origin.x;
    double o_y = ray.origin.y;
    double o_z = ray.origin.z;

    const double a = rotation(0, 0);
    const double b = rotation(1, 0);
    const double c = rotation(2, 0);
    const double d = rotation(0, 1);
    const double e = rotation(1, 1);
    const double f = rotation(2, 1);
    const double g = rotation(0, 2);
    const double h = rotation(1, 2);
    const double i = rotation(2, 2);

    const double u = origin.x;
    const double v = origin.y;
    const double w = origin.z;

    double r = radius;

    double coeff_c =
            -2 * a * a * o_x * u
            - 2 * b * b * o_y * v
            - 2 * c * c * o_z * w
            - 2 * d * d * o_x * u
            - 2 * e * e * o_y * v
            - 2 * f * f * o_z * w
            + a * a * o_x * o_x
            + a * a * u * u
            + b * b * o_y * o_y
            + b * b * v * v
            + c * c * o_z * o_z
            + c * c * w * w
            + d * d * o_x * o_x
            + d * d * u * u
            + e * e * o_y * o_y
            + e * e * v * v
            + f * f * o_z * o_z
            + f * f * w * w
            - r * r
            + 2 * a * o_x * b * o_y
            - 2 * a * o_x * b * v
            + 2 * a * o_x * c * o_z
            - 2 * a * o_x * c * w
            - 2 * a * u * b * o_y
            + 2 * a * u * b * v
            - 2 * a * u * c * o_z
            + 2 * a * u * c * w
            + 2 * b * o_y * c * o_z
            - 2 * b * o_y * c * w
            - 2 * b * v * c * o_z
            + 2 * b * v * c * w
            + 2 * d * o_x * e * o_y
            - 2 * d * o_x * e * v
            + 2 * d * o_x * f * o_z
            - 2 * d * o_x * f * w
            - 2 * d * u * e * o_y
            + 2 * d * u * e * v
            - 2 * d * u * f * o_z
            + 2 * d * u * f * w
            + 2 * e * o_y * f * o_z
            - 2 * e * o_y * f * w
            - 2 * e * v * f * o_z
            + 2 * e * v * f * w;
    double coeff_b =
            +2 * a * a * d_x * o_x
            - 2 * a * a * d_x * u
            + 2 * b * b * d_y * o_y
            - 2 * b * b * d_y * v
            + 2 * c * c * d_z * o_z
            - 2 * c * c * d_z * w
            + 2 * d * d * d_x * o_x
            - 2 * d * d * d_x * u
            + 2 * e * e * d_y * o_y
            - 2 * e * e * d_y * v
            + 2 * f * f * d_z * o_z
            - 2 * f * f * d_z * w
            + 2 * a * d_x * b * o_y
            - 2 * a * d_x * b * v
            + 2 * a * d_x * c * o_z
            - 2 * a * d_x * c * w
            + 2 * b * d_y * a * o_x
            - 2 * b * d_y * a * u
            + 2 * b * d_y * c * o_z
            - 2 * b * d_y * c * w
            + 2 * c * d_z * a * o_x
            - 2 * c * d_z * a * u
            + 2 * c * d_z * b * o_y
            - 2 * c * d_z * b * v
            + 2 * d * d_x * e * o_y
            - 2 * d * d_x * e * v
            + 2 * d * d_x * f * o_z
            - 2 * d * d_x * f * w
            + 2 * e * d_y * d * o_x
            - 2 * e * d_y * d * u
            + 2 * e * d_y * f * o_z
            - 2 * e * d_y * f * w
            + 2 * f * d_z * d * o_x
            - 2 * f * d_z * d * u
            + 2 * f * d_z * e * o_y
            - 2 * f * d_z * e * v;
    double coeff_a =
            2 * a * d_x * b * d_y
            + 2 * a * d_x * c * d_z
            + 2 * b * d_y * c * d_z
            + 2 * d * d_x * e * d_y
            + 2 * d * d_x * f * d_z
            + 2 * e * d_y * f * d_z
            + a * a * d_x * d_x
            + b * b * d_y * d_y
            + c * c * d_z * d_z
            + d * d * d_x * d_x
            + e * e * d_y * d_y
            + f * f * d_z * d_z;


    double discriminant = coeff_b * coeff_b - 4 * coeff_a * coeff_c;
    if (discriminant <= 0) return -1;

    double i1 = (-coeff_b - sqrt(discriminant)) / (2.0 * coeff_a);
    double i2 = (-coeff_b + sqrt(discriminant)) / (2.0 * coeff_a);

    Vector3 ipoint1 = ray.direction * i1 + ray.origin;
    Vector3 ipoint2 = ray.direction * i2 + ray.origin;

    double niceZ1 = applyMatrix(ipoint1-origin, rotation).z;
    double niceZ2 = applyMatrix(ipoint2-origin, rotation).z;

    if (i1 >= 0 && (i2 < 0 || !isGoodZ(niceZ2) || ray.direction * getNormalVector(ipoint2) > 0)) {
        // csak az 1. lehet jó
        return (isGoodZ(niceZ1) && ray.direction * getNormalVector(ipoint1) <= 0) ? i1 : -1;
    } else if (i2 >= 0 && (i1 < 0 || !isGoodZ(niceZ1) || ray.direction * getNormalVector(ipoint1) > 0)) {
        // csak az 2. lehet jó
        return (isGoodZ(niceZ2) && ray.direction * getNormalVector(ipoint2) <= 0) ? i2 : -1;
    } else {
        return -1;
    }


}


bool Cylinder::isGoodZ(double z) const {
    return z <= topZ && z >= bottomZ;
}

Vector3 Cylinder::getNormalVector(Vector3 &intersectionPoint) {
    auto n2 = intersectionPoint - origin;

    Vector3 n = applyMatrix(n2, rotation);
    n.z = 0;

    return applyMatrix(n, rotationInverse)._normalize();
}

void Cylinder::updateRotation(double angle) {
    rotation(0, 0) = cos(angle);
    rotation(1, 0) = 0;
    rotation(2, 0) = sin(angle);
    rotation(0, 1) = 0;
    rotation(1, 1) = 1;
    rotation(2, 1) = 0;
    rotation(0, 2) = -sin(angle);
    rotation(1, 2) = 0;
    rotation(2, 2) = cos(angle);

    rotationInverse = inverse(rotation);
}
