#include "example.h"

define_effect_fn(premul) {
    *r *= *a;
    *g *= *a;
    *b *= *a;
}

define_effect_fn(affine) {
    F32 X = *x * ctx->sx + (*y * ctx->kx + ctx->tx),
        Y = *x * ctx->ky + (*y * ctx->sy + ctx->ty);
    *x = X;
    *y = Y;
}

define_effect_fn(f16mad) {
    *ctx->dst = *ctx->x * *ctx->y + *ctx->z;
}
