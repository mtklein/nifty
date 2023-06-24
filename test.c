#include "effect.h"
#include "expect.h"
#include "unused.h"

#include "color.h"
#include "custom.h"
#include "matrix.h"

#define K (int)(sizeof(Half) / sizeof(half))

union Registers {
    struct {
        Half  r,g,b,a;
        Float x,y;
    };
    struct {
        half  R[K],G[K],B[K],A[K];
        float X[K],Y[K];
    };
};
static define_effect_fn(dump, union Registers *reg) {
    unused(end);
    reg->r = *r;
    reg->g = *g;
    reg->b = *b;
    reg->a = *a;
    reg->x = *x;
    reg->y = *y;
}

static void test_premul(void) {
    struct Color const c = {0.75f, 0.5f, 0.25f, 0.5f};
    union Registers reg;

    struct Effect program[] = {
        uniform_color(&c),
        premul,
        {dump, .vptr=&reg},
        done,
    };
    run(program,1);

    for (int i = 0; i < (int)(sizeof(Half)/sizeof(half)); i++) {
        expect((float)reg.R[i] == 0.375f);
        expect((float)reg.G[i] == 0.250f);
        expect((float)reg.B[i] == 0.125f);
        expect((float)reg.A[i] == 0.500f);
    }
}

int main(void) {
    test_premul();
    (void)affine;
    (void)half_mad;
    return 0;
}
