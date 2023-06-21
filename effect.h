#pragma once

typedef _Float16 __attribute__((vector_size(16))) F16;
typedef  float   __attribute__((vector_size(32))) F32;

struct Opaque;
struct Effect {
    void (*fn)(struct Effect*, int end, struct Opaque, struct Opaque);
    void *ctx;
};

void run(struct Effect const *program, int n);

#define declare_effect_fn(name, Ctx) \
    "Declare an effect function with given name and context type."

#define define_effect_fn(name) \
    "As if void name(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, Ctx *ctx, int end)"

#include "effect_details.h"
