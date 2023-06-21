#pragma once

#if defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
    typedef _Float16 half;
#else
    typedef  float   half;
#endif

typedef half  __attribute__((vector_size(16)))                                          Half;
typedef float __attribute__((vector_size((sizeof(Half)/sizeof(half)) * sizeof(float)))) Float;

struct Opaque;
struct Effect {
    void (*fn)(struct Effect const*, int end, struct Opaque, struct Opaque);
    void *ctx;
};

extern struct Effect const done;

void run(struct Effect const program[], int n);

// Details...

struct Opaque { Half val[4]; };

#define define_effect_fn(name,...) \
    void name(struct Effect const *ip, int end, struct Opaque c, struct Opaque p);           \
    static void name##_(Half*, Half*, Half*, Half*, Float*, Float*, int, __VA_ARGS__);       \
    void name(struct Effect const *ip, int end, struct Opaque c, struct Opaque p) {          \
        Float xy[2];                                                                         \
        _Static_assert(sizeof xy <= sizeof p, "");                                           \
        __builtin_memcpy(xy, &p, sizeof xy);                                                 \
        name##_(c.val+0, c.val+1, c.val+2, c.val+3, xy+0, xy+1, end, ip->ctx);               \
        __builtin_memcpy(&p, xy, sizeof xy);                                                 \
        ip[1].fn(ip+1,end,c,p);                                                              \
    }                                                                                        \
    static void name##_(Half *r, Half *g, Half *b, Half *a, Float *x, Float *y,int end,__VA_ARGS__)
