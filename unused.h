#pragma once

static void unused_(int x, ...) { (void)x; }
#define unused(...) unused_(0, __VA_ARGS__)
