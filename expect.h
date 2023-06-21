#pragma once

void abort(void);
int  dprintf(int, char const*, ...);
#define expect(x) if (!(x)) dprintf(2, "%s:%d expect(%s)\n", __FILE__,__LINE__,#x), abort()
