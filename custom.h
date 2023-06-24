#pragma once
#include "effect.h"

struct HalfBinary {
    Half       *dst;
    Half const *x,*y;
};

struct HalfTernary {
    Half       *dst;
    Half const *x,*y,*z;
};

struct Effect half_add(struct HalfBinary  const*);
struct Effect half_sub(struct HalfBinary  const*);
struct Effect half_mul(struct HalfBinary  const*);
struct Effect half_div(struct HalfBinary  const*);
struct Effect half_mad(struct HalfTernary const*);
