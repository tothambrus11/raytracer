#pragma once

#include "SDL2/SDL.h"
#include "string"

using namespace std;


struct Color {
    Color() = default;

    double r = 0, g = 0, b = 0;

    Color(double r, double g, double b) : r(r), g(g), b(b) {}

    Color(double all) : r(all), g(all), b(all) {}

    [[nodiscard]] std::string toString() const {
        return "Color(" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ")";
    }

    inline Color operator*(double s) const {
        return {r * s, g * s, b * s};
    }

    inline Color operator*(Color c) const {
        return {r * c.r, g * c.g, b * c.b};
    }

    inline void operator+=(Color c) {
        r += c.r;
        g += c.g;
        b += c.b;
    }

    void normalize() {
        r = max(min(1.0, r), 0.0);
        g = max(min(1.0, g), 0.0);
        b = max(min(1.0, b), 0.0);
    }

    inline Color minZero() const{
        return {max(.0,r),max(.0,g),max(.0,b)};
    }
};

struct RGB255Color {
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;

    RGB255Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b) {}

    RGB255Color() {}

    static RGB255Color from(Color c) {
        c.normalize();
        return {(Uint8) (c.r * 255), (Uint8) (c.g * 255), (Uint8) (c.b * 255)};
    }
};