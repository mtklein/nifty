#pragma once
#include "effect.h"

extern struct Effect const premul;

struct Color {
    half r,g,b,a;
};
struct Effect uniform_color(struct Color const*);
