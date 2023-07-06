#include "custom.h"
#include "unused.h"

static define_effect_fn(half_mad_, struct HalfTernary const *arg) {
    unused(r,g,b,a,x,y,end);
    *arg->dst = *arg->x * *arg->y + *arg->z;
}

struct Effect half_mad(struct HalfTernary const *arg) {
    return (struct Effect){half_mad_, .cptr=arg};
}
