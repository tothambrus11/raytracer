//
// Created by ambru on 2022. 01. 24..
//

#include "math.h"
#include "Cylinder.h"


Cylinder::Cylinder(const Vector3 &origin, double radius, double topZ, double bottomZ, Color c, Material material)
        : origin(origin), radius(radius), topZ(topZ), bottomZ(bottomZ) {
    this->color = c;
    this->material = material;
}

double Cylinder::intersectsRayAt(Ray &ray) {
    // (x-u)**2 + (y-v)**2 = r**2; any z between topZ and bottomZ
    // (O_x+D_x*t-u)**2 + (O_y+D_y*t-v)**2 = r**2;
    // P=O+D*t
    // (O_x + D_x * t-u)^2 + (O_Y + D_y * t-v)^2 = r^2;
    // O_x^2 + D_x^2 * t^2 + 2*O_x*D_x*t + O_y^2 + D_y^2 * t^2 + 2*O_y*D_y*t = r^2;
    // (D_x^2 + D_y^2) * t^2 + (2*O_x*D_x + 2*O_y*D_y) * t + (O_x^2 + O_y^2 - r^2) = 0

    double a = (ray.direction.x * ray.direction.x) + (ray.direction.y * ray.direction.y);
    double b = 2 * (ray.origin.x * ray.direction.x + ray.origin.y * ray.direction.y);
    double c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y - radius * radius;

    double D_x = ray.direction.x;
    double D_y = ray.direction.y;
    double O_x = ray.origin.x;
    double O_y = ray.origin.y;
    double discriminant = pow(-2 * D_x * O_x + 2 * D_x * origin.x - 2 * D_y * O_y + 2 * D_y * origin.y, 2) -
                          4 * (-D_x * D_x - D_y * D_y) *
                          (-O_x * O_x + 2 * O_x * origin.x - O_y * O_y + 2 * O_y * origin.y + radius * radius -
                           origin.x * origin.x - origin.y * origin.y);
    if (discriminant < 0) return -1;
    double i1 = (-sqrt(discriminant) + 2 * D_x * O_x - 2 * D_x * origin.x + 2 * D_y * O_y - 2 * D_y * origin.y) /
                (2 * (-D_x * D_x - D_y * D_y));
    double i2 = (sqrt(discriminant) + 2 * D_x * O_x - 2 * D_x * origin.x + 2 * D_y * O_y - 2 * D_y * origin.y) /
                (2 * (-D_x * D_x - D_y * D_y));

    if (i1 < 0 || !isGoodZ((ray.origin + ray.direction * i1).z)) {
        return isGoodZ((ray.origin+ray.direction*i2).z) ? i2 : -1;
    }
    if (i2 < 0 || !isGoodZ((ray.origin + ray.direction * i2).z)) {
        return isGoodZ((ray.origin+ray.direction*i1).z) ? i1 : -1;
    }
    return min(i1, i2);
}


Color Cylinder::calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                      vector<HittableObject *> &objects, vector<PointLight *> &lights) {
    if (remainingIterations == 0) {
        return {};
    }
    if (remainingIterations <= 3) {
        //cout << ((int) remainingIterations) << " ";
    }

    auto n = (intersectionPoint-origin);
    n.z = 0;
    auto e = n * ((incomingRay.direction * -1) * n);
    auto D2 = ((e * 2) + incomingRay.direction).normalize();
    Ray outgoingRay(intersectionPoint, D2);
    if(D2 * n < 0) return {0,0,.4};

    if (remainingIterations == 4) {
        //cout << intersectionPoint.toString() << " " << objects.size() << " " << lights.size() << endl;
    }
    Color c;

    // ambient reflection
    c += material.color; // todo multiply with ambient light

    for (PointLight *&light: lights) {
        // check for shadows

        bool foundI = false;
        for (auto o: objects) {
            Ray r = Ray(intersectionPoint, (light->origin - intersectionPoint).normalize());
            if (o->intersectsRayAt(r) > 0 && o != this) {
                foundI = true;
                break;
            }
        }
        if (foundI) { continue; }


        auto L = (light->origin - intersectionPoint).normalize(); // direction to the light source
        // diffuse reflection

        auto lightDirNormalVecCos = L * n;
        if (lightDirNormalVecCos < 0) continue;

        c += material.d * light->color * lightDirNormalVecCos;
        if (remainingIterations == 4) {
            //  cout << "l1 \n";
        }

        auto e2 = n * lightDirNormalVecCos;
        auto LReflection = (e2 * 2 - L).normalize();
        if (LReflection * incomingRay.direction > 0) {
            continue;
        }
        if (remainingIterations == 4) {
            /// cout << "l2 ";
        }

        c += (material.s * pow(LReflection * incomingRay.direction * -1, 16) * light->color).minZero();

    }

    HittableObject *nearestObject = nullptr;
    double minDistance;
    for (auto &object: objects) {
        double distance = object->intersectsRayAt(outgoingRay);
        if (distance > 0 && (nearestObject == nullptr || distance < minDistance) && object != this) {
            minDistance = distance;
            nearestObject = object;
        }
    }

    if (nearestObject != nullptr) {
        Color noc = nearestObject->calculateEmittedLight(remainingIterations - 1, outgoingRay,
                                                         outgoingRay.direction * minDistance + outgoingRay.origin,
                                                         objects, lights);
        c += (noc * material.reflection);
    }

    return c;
}

bool Cylinder::isGoodZ(double z) const {
    return z-origin.z <= topZ && z-origin.z >= bottomZ;
}
