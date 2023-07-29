#include "effect.h"
#include "unused.h"

static void done_(struct Effect const *ip, int end, Half r , Half g , Half b , Half a
                                                  , Half xl, Half xh, Half yl, Half yh) {
    unused(ip,end, r,g,b,a, xl,xh, yl,yh);
}
struct Effect const done = {done_, .vptr=(void*)0};


static void loop_(struct Effect const *ip, int end, Half r , Half g , Half b , Half a
                                                  , Half xl, Half xh, Half yl, Half yh) {
    struct Loop *arg = ip->vptr;
    int const jmp = --arg->n ? arg->jmp : 1;
    ip[jmp].fn(ip+jmp,end, r,g,b,a, xl,xh, yl,yh);
}
struct Effect loop(struct Loop *arg) {
    return (struct Effect){loop_, .vptr=arg};
}


void run(struct Effect const program[], int n) {
    int const K = (int)(sizeof(Half) / sizeof(half));
    Half const z = {0};
    for (int end = 0; n;) {
        end += n < K ? n : K;
        n   -= n < K ? n : K;
        program->fn(program,end, z,z,z,z, z,z,z,z);
    }
}
