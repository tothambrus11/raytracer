//
// Created by ambru on 2021. 11. 23..
//

#include "HittableObject.h"

Color HittableObject::calculateEmittedLight(Uint8 remainingIterations, Ray &incomingRay, Vector3 intersectionPoint,
                                            vector<HittableObject *> &objects, vector<PointLight *> &lights) {
    if (remainingIterations == 0) {
        return {};
    }


    auto n = this->getNormalVector(intersectionPoint);

    auto e = n * ((incomingRay.direction * -1) * n);
    auto D2 = ((e * 2) + incomingRay.direction).normalize();
    Ray outgoingRay(intersectionPoint, D2);

    if (remainingIterations == 4) {
        //cout << intersectionPoint.toString() << " " << objects.size() << " " << lights.size() << endl;
    }
    Color c;

    // ambient reflection
    c += material.color; // todo multiply with ambient light

    for (PointLight *&light: lights) {
        // check for shadows

        bool foundI = false;
        double lightDistance = (light->origin-intersectionPoint).length();
        for (auto o: objects) {
            Ray r = Ray(intersectionPoint, (light->origin - intersectionPoint).normalize());
            double isDist = o->intersectsRayAt(r);
            if (isDist > 0.1 && isDist < lightDistance /*&& o != this*/) {
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
