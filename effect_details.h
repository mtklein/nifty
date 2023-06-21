#pragma once

struct Opaque { F16 val[4]; };

#undef  define_effect_fn
#define define_effect_fn(name,...) \
    void name(struct Effect const *ip, int end, struct Opaque c, struct Opaque p);   \
    static void name##_(F16*, F16*, F16*, F16*, F32*, F32*, int, __VA_ARGS__);       \
    void name(struct Effect const *ip, int end, struct Opaque c, struct Opaque p) {  \
        F32 xy[2];                                                                   \
        _Static_assert(sizeof xy == sizeof p, "");                                   \
        __builtin_memcpy(xy, &p, sizeof xy);                                         \
        name##_(c.val+0, c.val+1, c.val+2, c.val+3, xy+0, xy+1, end, ip->ctx);       \
        __builtin_memcpy(&p, xy, sizeof xy);                                         \
        ip[1].fn(ip+1,end,c,p);                                                      \
    }                                                                                \
    static void name##_(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, int end, __VA_ARGS__)
