#pragma once
#include "effect.h"

struct Scanline {
    int x0,y;
};
struct Effect scanline(struct Scanline const*);

struct Affine {
    float sx,kx,tx,
          ky,sy,ty;
};
struct Effect affine(struct Affine const*);
