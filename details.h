#pragma once

struct Opaque { F16 val[4]; };

#undef declare_effect_fn
#undef  define_effect_fn

#define declare_effect_fn(name, Ctx) \
    typedef Ctx name##_Ctx;          \
    void name(struct Effect *ip, int end, struct Opaque c, struct Opaque p)

#define define_effect_fn(name) \
    static void name##_(F16*, F16*, F16*, F16*, F32*, F32*, name##_Ctx*, int); \
    void name(struct Effect *ip, int end, struct Opaque c, struct Opaque p) {  \
        F32 xy[2];                                                             \
        _Static_assert(sizeof xy == sizeof p, "");                             \
        __builtin_memcpy(xy, &p, sizeof xy);                                   \
        name##_(c.val+0, c.val+1, c.val+2, c.val+3, xy+0, xy+1, ip->ctx, end); \
        __builtin_memcpy(&p, xy, sizeof xy);                                   \
        ip[1].fn(ip+1,end,c,p);                                                \
    }                                                                          \
    static void name##_(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, name##_Ctx *ctx, int end)
