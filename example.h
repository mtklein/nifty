#pragma once
#include "effect.h"

declare_effect_fn(premul, void);

struct Affine {
    float sx,kx,tx,
          ky,sy,ty;
};
declare_effect_fn(affine, struct Affine const);

struct F16Ternary {
    F16       *dst;
    F16 const *x,*y,*z;
};
declare_effect_fn(f16mad, struct F16Ternary const);
