#pragma once
#include "SDL2/SDL.h"

struct Color {
    Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Uint8 r = 0, g = 0, b = 0;

    Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b) {}
};