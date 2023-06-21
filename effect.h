#pragma once

typedef _Float16 __attribute__((vector_size(16))) F16;
typedef  float   __attribute__((vector_size(32))) F32;

struct Opaque;

struct Effect {
    void (*fn)(struct Effect const*, int end, struct Opaque, struct Opaque);
    void *ctx;
};

extern struct Effect const done;

void run(struct Effect const program[], int n);

#define define_effect_fn(name, ...) \
    "As if void name(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, int end, __VA_ARGS__)"

#include "effect_details.h"
