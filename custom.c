#include "custom.h"
#include "unused.h"

static define_effect_fn(half_mad_, struct HalfTernary const *arg) {
    *arg->dst = *arg->x * *arg->y + *arg->z;
    unused(r,g,b,a,x,y,end);
}

struct Effect half_mad(struct HalfTernary const *arg) {
    return (struct Effect){half_mad_, .cptr=arg};
}
