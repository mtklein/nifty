#include "effect.h"
#include "expect.h"
#include "unused.h"

#include "color.h"
#include "coords.h"
#include "custom.h"

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

    for (int i = 0; i < K; i++) {
        expect((float)reg.R[i] == 0.375f);
        expect((float)reg.G[i] == 0.250f);
        expect((float)reg.B[i] == 0.125f);
        expect((float)reg.A[i] == 0.500f);
    }
}

static void test_scanline(void) {
    struct Scanline const xy = {4,7};
    union Registers reg;

    struct Effect program[] = {
        scanline(&xy),
        {dump, .vptr=&reg},
        done,
    };

    run(program,K);
    for (int i = 0; i < K; i++) {
        expect((float)reg.X[i] - (float)i == 4.5f);
        expect((float)reg.Y[i]            == 7.5f);
    }

    run(program,2*K);
    for (int i = 0; i < K; i++) {
        expect((float)reg.X[i] - (float)(i+K) == 4.5f);
        expect((float)reg.Y[i]                == 7.5f);
    }
}

int main(void) {
    test_premul();
    test_scanline();
    return 0;
}
