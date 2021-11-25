#include "Vector3.h"

Vector3::Vector3() {
    x=0;
    y=0;
    z=0;
}

Vector3 Vector3::_setLength(double newLength) {
    *this *= (newLength / length());
    return *this;
}

Vector3 Vector3::setLength(double newLength) const {
    return *this * (newLength / length());
}

Vector3 Vector3::_normalize() {
    *this /= length(); // = _setLength(1)
    return *this;
}

Vector3 Vector3::normalize() const {
    return *this / length();
}

Vector3 Vector3::mult(double s) const {
    return copy() * s;
}

Vector3 Vector3::_div(double s) {
    (*this) /= s;
    return *this;
}

Vector3 Vector3::div(double s) const {
    return copy() / s;
}

double Vector3::scalarMult(Vector3 &b) const {
    return *this * b;
}

Vector3 Vector3::copy() const {
    return *this;
}

Vector3 Vector3::crossProduct(Vector3 a, Vector3 b) {
    return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
    };
}

double &Vector3::operator[](size_t index) {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw "Invalid index"; // todo make a valid exception
    };
}

void Vector3::operator+=(Vector3 a) {
    x += a.x;
    y += a.y;
    z += a.z;
}

void Vector3::operator-=(Vector3 a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
}

Vector3 Vector3::operator+(Vector3 a) const {
    return {x + a.x, y + a.y, z + a.z};
}

Vector3 Vector3::operator-(Vector3 a) const {
    return {x - a.x, y - a.y, z - a.z};
}

void Vector3::operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;
}

void Vector3::operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
}

double Vector3::operator*(Vector3 other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::operator*(double s) const {
    return {x * s, y * s, z * s};
}

Vector3 Vector3::operator/(double s) const {
    return {x / s, y / s, z / s};
}

Vector3::operator std::string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + "," + std::to_string(z) + ")";
}

double Vector3::sq() const {
    return x*x + y*y + z*z;
}

std::string Vector3::toString() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + "," + std::to_string(z) + ")";
}
