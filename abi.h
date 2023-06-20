#pragma once

typedef _Float16 __attribute__((vector_size(16))) F16;
typedef  float   __attribute__((vector_size(32))) F32;

struct Opaque;
struct Effect {
    void (*fn)(struct Effect*, struct Opaque, struct Opaque);
    void *ctx;
};

#define declare_effect_fn(name, CtxType) \
    "Declare an effect function with given name and context type."

#define define_effect_fn(name) \
    // { ... your code here modifying F16 *r,*g,*b,*a and/or F32 *x,*y using CtxType *ctx ... }
    // as if declared void name(F16 *r, F16 *g, F16 *b, F16 *a, F32 *x, F32 *y, CtxType *ctx)


// Implementation details.

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
