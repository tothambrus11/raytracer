#pragma once

#include <cstdio>
#include <cmath>
#include <string>

class Vector3 {
public:

    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector3();

    double x, y, z;

    inline double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    [[nodiscard]] Vector3 setLength(double newLength) const;

    Vector3 _setLength(double newLength);

    Vector3 _normalize();

    [[nodiscard]] Vector3 normalize() const;

    inline Vector3 _add(Vector3 &other) {
        return _add(other.x, other.y, other.z);
    }

    inline Vector3 add(Vector3 &other) {
        return add(x, y, z);
    }

    inline Vector3 _add(double _x, double _y, double _z) {
        x += _x;
        y += _y;
        z += _z;
        return *this;
    }

    inline Vector3 add(double _x, double _y, double _z) {
        return copy()._add(_x, _y, _z);
    }

    inline Vector3 _sub(Vector3 &other) {
        return _sub(other.x, other.y, other.z);
    }

    inline Vector3 sub(Vector3 &other) {
        return copy()._sub(other);
    }

    inline Vector3 _sub(double _x, double _y, double _z) {
        x -= _x;
        y -= _y;
        z -= _z;
        return *this;
    }

    inline Vector3 sub(double _x, double _y, double _z) {
        return copy()._sub(_x, _y, _z);
    }

    inline Vector3 _mult(double s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    Vector3 mult(double s) const;

    Vector3 _div(double s);

    Vector3 div(double s) const;

    double scalarMult(Vector3 &other) const;

    Vector3 copy() const;

    static Vector3 crossProduct(Vector3 a, Vector3 b);

    double &operator[](size_t index);

    void operator+=(Vector3 a);

    void operator-=(Vector3 a);

    void operator/=(double s);

    void operator*=(double s);

    Vector3 operator+(Vector3 a) const;

    Vector3 operator-(Vector3 a) const;

    /**
     * Dot / Scalar product
     * @param other
     * @return
     */
    double operator*(Vector3 other) const;

    /**
     * Multiply by color number
     * @param s
     * @return
     */
    Vector3 operator*(double s) const;

    /**
     * Divide by color number
     * @param a
     * @return
     */
    Vector3 operator/(double s) const;

    explicit operator std::string() const;

    [[nodiscard]] double sq() const;

    std::string toString();

    inline static Vector3 fromTo(Vector3 from, Vector3 to){
        return to - from;
    }
};