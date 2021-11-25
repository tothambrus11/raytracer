#include <Vector3.h>
#include <Ray.h>

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}

Ray::Ray() {
    origin = {0, 0, 0};
    direction = {0, 0, 1};
}