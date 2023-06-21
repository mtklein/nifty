#include "effect.h"

static void done_(struct Effect const *ip, int end, struct Opaque c, struct Opaque p) {
    (void)ip;
    (void)end;
    (void)c;
    (void)p;
}
struct Effect const done = {done_, (void*)0};

void run(struct Effect const program[], int n) {
    int const K = sizeof(F32) / sizeof(float);
    struct Opaque const zero = {0};
    for (int end = 0; n;) {
        end += n < K ? n : K;
        n   -= n < K ? n : K;
        program->fn(program,end,zero,zero);
    }
}
