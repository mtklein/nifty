#pragma once
#include "effect.h"

struct Affine {
    float sx,kx,tx,
          ky,sy,ty;
};

struct Effect affine(struct Affine const*);
