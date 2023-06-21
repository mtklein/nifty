#include "effect.h"

static void done_(struct Effect const *ip, int end, Half r , Half g , Half b , Half a
                                                  , Half xl, Half xh, Half yl, Half yh) {
    (void)ip;
    (void)end;
    (void)r;
    (void)g;
    (void)b;
    (void)a;
    (void)xl;
    (void)xh;
    (void)yl;
    (void)yh;
}
struct Effect const done = {done_, (void*)0};

void run(struct Effect const program[], int n) {
    int const K = sizeof(Float) / sizeof(float);
    Half const z = {0};
    for (int end = 0; n;) {
        end += n < K ? n : K;
        n   -= n < K ? n : K;
        program->fn(program,end, z,z,z,z, z,z,z,z);
    }
}
