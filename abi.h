#pragma once

typedef _Float16 __attribute__((vector_size(16))) F16;
typedef  float   __attribute__((vector_size(32))) F32;

struct Opaque;
struct Effect {
    void (*fn)(struct Effect*, struct Opaque, struct Opaque);
    void *ctx;
};

#define declare_effect_fn(name, CtxType) \
    "Declare an effect function with given name and context type."

#define define_effect_fn(name) \
    // { ... your code here modifying F16 *r,*g,*b,*a and/or F32 *x,*y using CtxType *ctx ... }
    // as if declared void name(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, CtxType *ctx)


#include "details.h"
