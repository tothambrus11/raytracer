//
// Created by ambru on 2021. 11. 25..
//

#include "Octahedron.h"
#include "SDL2/SDL.h"

double Octahedron::intersectsRayAt(Ray &ray) {
    // |dx*c + o_x - x_0| + |dy*c + o_y - y_0| + |dz*c +o_z - z_0| = k
    // p=d*c + o

    // [ dx*c + o_x - x_0 > 0 && dy*c + o_y - y_0 > 0 && dz*c +o_z - z_0 ]

    // dx*c + o_x - x_0 + dy*c + o_y - y_0 + dz*c +o_z - z_0 = s
    // dx*c + dy*c + dz*c = s + x_0 + y_0 + z_0 - o_x - o_y - o_z
    // c * (dx + dy + dz) = s + x_0 + y_0 + z_0 - o_x - o_y - o_z
    // c = (s + x_0 + y_0 + z_0 - o_x - o_y - o_z) / (dx + dy + dz)
    // c = (s + x_0*i + y_0*j + z_0*k - o_x*i - o_y*j - o_z*k) / (dx*i + dy*j + dz*k)

    // 300

    double minC = -1;
    for (auto &i: {-1, 1}) {
        for (auto &j: {-1, 1}) {
            for (auto &k: {-1, 1}) {
                auto c = (size + origin.x * i + origin.y * j + origin.z * k - ray.origin.x * i - ray.origin.y * j -
                          ray.origin.z * k) /
                         (ray.direction.x * i + ray.direction.y * j + ray.direction.z * k);
                if ((ray.direction.x * c + ray.origin.x - origin.x) * i >= 0 &&
                    (ray.direction.y * c + ray.origin.y - origin.y) * j >= 0 &&
                    (ray.direction.z * c + ray.origin.z - origin.z) * k >= 0) {
                    if (minC == -1 || minC > c) {
                        minC = c;
                    }
                }
            }
        }
    }
    return minC;
}

Octahedron::Octahedron(const Vector3 &origin, double size) : origin(origin),
                                                             size(size) {}

Vector3 Octahedron::getNormalVector(Vector3 &intersectionPoint) {
    return (intersectionPoint - origin)._normalize(); // todo
}

