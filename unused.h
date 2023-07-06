#pragma once

static int unused_(int x, ...) { return x; }
#define unused(...) int __attribute__((unused)) unused = unused_(0, __VA_ARGS__)
