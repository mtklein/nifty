#pragma once

#if defined(__GNUC__) || defined(__clang__)
    #define vector_size(sz) __attribute__((__vector_size__(sz)))
#else
    #define vector_size(sz)
#endif

#if defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
    typedef _Float16 half;
#else
    typedef  float   half;
#endif

#if defined(__AVX__)
    typedef half vector_size(32) Half;
#else
    typedef half vector_size(16) Half;
#endif

typedef float vector_size(sizeof(Half)/sizeof(half) * sizeof(float)) Float;

#undef vector_size

extern struct Effect {
    void (*fn)(struct Effect const*,int, Half,Half,Half,Half, Half,Half,Half,Half);
    union {
        void       *vptr;
        void const *cptr;
    };
} const done;

void run(struct Effect const program[], int n);

#define define_effect_fn(name, ...)                                                          \
    void name(struct Effect const*, int, Half,Half,Half,Half, Half,Half,Half,Half);          \
    static void name##_(Half*,Half*,Half*,Half*, Float*,Float*, int, __VA_ARGS__);           \
    void name(struct Effect const *ip, int end, Half r , Half g , Half b , Half a            \
                                              , Half xl, Half xh, Half yl, Half yh) {        \
        union { Half h[2]; Float f; } x = {{xl,xh}}, y = {{yl,yh}};                          \
        name##_(&r,&g,&b,&a, &x.f,&y.f, end, ip->vptr);                                      \
        ip[1].fn(ip+1,end, r,g,b,a, x.h[0],x.h[1], y.h[0],y.h[1]);                           \
    }                                                                                        \
    void name##_(Half *r, Half *g, Half *b, Half *a, Float *x, Float *y, int end, __VA_ARGS__)
