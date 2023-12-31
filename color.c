#include "color.h"
#include "unused.h"

static define_effect_fn(premul_, void *ctx) {
    unused(x,y,end,ctx);
    *r *= *a;
    *g *= *a;
    *b *= *a;
}
struct Effect const premul = {premul_, .vptr=(void*)0};

static define_effect_fn(uniform_color_, struct Color const *c) {
    unused(x,y,end);
    *r = c->r - (Half){0};
    *g = c->g - (Half){0};
    *b = c->b - (Half){0};
    *a = c->a - (Half){0};
}
struct Effect uniform_color(struct Color const *c) {
    return (struct Effect){uniform_color_, .cptr=c};
}
