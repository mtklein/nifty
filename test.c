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
static define_effect_fn(load, union Registers const *reg) {
    unused(end);
    *r = reg->r;
    *g = reg->g;
    *b = reg->b;
    *a = reg->a;
    *x = reg->x;
    *y = reg->y;
}
static define_effect_fn(dump, union Registers *reg) {
    unused(end);
    reg->r = *r;
    reg->g = *g;
    reg->b = *b;
    reg->a = *a;
    reg->x = *x;
    reg->y = *y;
}

static void test_uniform_color(void) {
    struct Color const c = {0.75f, 0.5f, 0.25f, 0.5f};
    union Registers reg;

    struct Effect program[] = {
        uniform_color(&c),
        {dump, .vptr=&reg},
        done,
    };

    run(program,K);
    for (int i = 0; i < K; i++) {
        expect((float)reg.R[i] == 0.75f);
        expect((float)reg.G[i] == 0.50f);
        expect((float)reg.B[i] == 0.25f);
        expect((float)reg.A[i] == 0.50f);
    }
}

static void test_premul(void) {
    union Registers reg = {
        .R = {0.75f},
        .G = {0.50f},
        .B = {0.25f},
        .A = {0.50f},
    };

    struct Effect program[] = {
        {load, .cptr=&reg},
        premul,
        {dump, .vptr=&reg},
        done,
    };

    run(program,1);
    expect((float)reg.R[0] == 0.375f);
    expect((float)reg.G[0] == 0.250f);
    expect((float)reg.B[0] == 0.125f);
    expect((float)reg.A[0] == 0.500f);
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
        expect(reg.X[i] - (float)i == 4.5f);
        expect(reg.Y[i]            == 7.5f);
    }

    run(program,2*K);
    for (int i = 0; i < K; i++) {
        expect(reg.X[i] - (float)(i+K) == 4.5f);
        expect(reg.Y[i]                == 7.5f);
    }
}

static void test_affine(void) {
    struct Affine const m = {
        2,1,3,
        0,5,4,
    };
    union Registers reg = {
        .X = {1},
        .Y = {3},
    };

    struct Effect program[] = {
        {load, .cptr=&reg},
        affine(&m),
        {dump, .vptr=&reg},
        done,
    };

    run(program,1);
    expect(reg.X[0] ==  8.0f);
    expect(reg.Y[0] == 19.0f);
}

static define_effect_fn(square_x, void* arg) {
    unused(r,g,b,a,y,end,arg);
    *x *= *x;
}

static void test_loop(void) {
    union Registers reg = {
        .X = {2},
    };
    struct LoopArg l = {.jmp=-1, .n=4};

    struct Effect program[] = {
        {load, .cptr=&reg},
        {square_x, .vptr=(void*)0},
        loop(&l),
        {dump, .vptr=&reg},
        done,
    };

    run(program,1);
    expect(reg.X[0] == 65536.0f);
    expect(l.n == 0);
}

int main(void) {
    test_uniform_color();
    test_premul();
    test_scanline();
    test_affine();
    test_loop();
    return 0;
}
