#include "effect.h"
#include "expect.h"
#include "unused.h"
#define len(x) (int)(sizeof(x) / sizeof((x)[0]))

struct Registers {
    Half r,g,b,a;
    Float    x,y;
};
static define_effect_fn(dump, struct Registers *reg) {
    unused(end);
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
    unused(x,y,end);
    *r = c->r - (Half){0};
    *g = c->g - (Half){0};
    *b = c->b - (Half){0};
    *a = c->a - (Half){0};
}

static define_effect_fn(premul, void *ctx) {
    unused(x,y,end,ctx);
    *r *= *a;
    *g *= *a;
    *b *= *a;
}

struct Affine {
    float sx,kx,tx,
          ky,sy,ty;
};
static define_effect_fn(affine, struct Affine const *m) {
    unused(r,g,b,a,end);
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
    unused(r,g,b,a,x,y,end);
    *arg->dst = *arg->x * *arg->y + *arg->z;
}

static void test_premul(void) {
    struct Color c = {0.75f, 0.5f, 0.25f, 0.5f};
    struct Registers reg;

    struct Effect program[] = {
        {uniform, &c},
        { premul, (void*)0},
        {   dump, &reg},
        done,
    };
    run(program,1);

    for (int i = 0; i < len(reg.r); i++) {
        expect((float)reg.r[i] == 0.375f);
        expect((float)reg.g[i] == 0.250f);
        expect((float)reg.b[i] == 0.125f);
        expect((float)reg.a[i] == 0.500f);
    }
}

int main(void) {
    test_premul();
    (void)affine;
    (void)half_mad;
    return 0;
}
