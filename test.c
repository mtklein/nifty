#include "effect.h"
#include "expect.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define len(x) (int)(sizeof(x) / sizeof((x)[0]))

struct Registers {
    Half r,g,b,a;
    Float    x,y;
};
static define_effect_fn(dump, struct Registers *reg) {
    reg->r = *r;
    reg->g = *g;
    reg->b = *b;
    reg->a = *a;
    reg->x = *x;
    reg->y = *y;
}

struct Color {
    half r,g,b,a;
};
static define_effect_fn(uniform, struct Color const *c) {
    *r = c->r - (Half){0};
    *g = c->g - (Half){0};
    *b = c->b - (Half){0};
    *a = c->a - (Half){0};
}

static define_effect_fn(premul, void *unused) {
    *r *= *a;
    *g *= *a;
    *b *= *a;
}

struct Affine {
    float sx,kx,tx,
          ky,sy,ty;
};
static define_effect_fn(affine, struct Affine const *m) {
    Float X = *x * m->sx + (*y * m->kx + m->tx),
          Y = *x * m->ky + (*y * m->sy + m->ty);
    *x = X;
    *y = Y;
}

struct HalfTernary {
    Half       *dst;
    Half const *x,*y,*z;
};
static define_effect_fn(half_mad, struct HalfTernary const *arg) {
    *arg->dst = *arg->x * *arg->y + *arg->z;
}

static void test_premul(void) {
    struct Color c = {0.75, 0.5, 0.25, 0.5};
    struct Registers reg;

    struct Effect program[] = {
        {uniform, &c},
        { premul, (void*)0},
        {   dump, &reg},
        done,
    };
    run(program,1);

    for (int i = 0; i < len(reg.r); i++) {
        expect((double)reg.r[i] == 0.375);
        expect((double)reg.g[i] == 0.250);
        expect((double)reg.b[i] == 0.125);
        expect((double)reg.a[i] == 0.500);
    }
}

int main(void) {
    test_premul();
    (void)affine;
    (void)half_mad;
    return 0;
}
