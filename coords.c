#include "coords.h"
#include "unused.h"

#define K (int)(sizeof(Half) / sizeof(half))

static int begin(int end) {
    if (end & (K-1)) {
        return end & ~(K-1);
    }
    return end - K;
}

static define_effect_fn(scanline_, struct Scanline const *arg) {
    union {
        float val[K];
        Float vec;
    } iota;
    for (int i = 0; i < K; i++) {
        iota.val[i] = i;
    }
    *x = arg->x0 + begin(end) + 0.5f + iota.vec;
    *y = arg->y               + 0.5f - (Float){0};
    unused(r,g,b,a);
}
struct Effect scanline(struct Scanline const *arg) {
    return (struct Effect){scanline_, .cptr=arg};
}


static define_effect_fn(affine_, struct Affine const *m) {
    Float X = *x * m->sx + (*y * m->kx + m->tx),
          Y = *x * m->ky + (*y * m->sy + m->ty);
    *x = X;
    *y = Y;
    unused(r,g,b,a,end);
}
struct Effect affine(struct Affine const *m) {
    return (struct Effect){affine_, .cptr=m};
}
