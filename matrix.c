#include "matrix.h"
#include "unused.h"

static define_effect_fn(affine_, struct Affine const *m) {
    unused(r,g,b,a,end);
    Float X = *x * m->sx + (*y * m->kx + m->tx),
          Y = *x * m->ky + (*y * m->sy + m->ty);
    *x = X;
    *y = Y;
}

struct Effect affine(struct Affine const *m) {
    return (struct Effect){affine_, .cptr=m};
}
