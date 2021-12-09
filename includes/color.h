#pragma once

#include "SDL2/SDL.h"
#include "string"

using namespace std;


struct Color {
    Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Uint8 r = 0, g = 0, b = 0;

    Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b) {}

    [[nodiscard]] std::string toString() const {
        return "Color(" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ")";
    }

    Color operator*(double s) const {
        return {static_cast<Uint8>(r * s), static_cast<Uint8>(g * s), static_cast<Uint8>(b * s)};
    }

    void operator+=(Color c) {
        r = min(255, c.r + r);
        g = min(255, c.g + g);
        b = min(255, c.b + b);
    }
};