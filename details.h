#pragma once

struct Opaque { F16 val[4]; };

#undef declare_effect_fn
#define declare_effect_fn(name, CtxType) \
    typedef CtxType name##_CtxType;   \
    void name(struct Effect *ip, struct Opaque c, struct Opaque p)

#undef define_effect_fn
#define define_effect_fn(name) \
    static void name##_(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, name##_CtxType*); \
    void name(struct Effect *ip, struct Opaque c, struct Opaque p) {                      \
        F32 xy[2];                                                                        \
        _Static_assert(sizeof xy == sizeof p, "");                                        \
        __builtin_memcpy(xy, &p, sizeof xy);                                              \
        name##_(c.val+0, c.val+1, c.val+2, c.val+3, xy+0, xy+1, ip->ctx);                 \
        __builtin_memcpy(&p, xy, sizeof xy);                                              \
        ip[1].fn(ip+1,c,p);                                                               \
    }                                                                                     \
    static void name##_(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, name##_CtxType *ctx)
