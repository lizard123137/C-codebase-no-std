#include "math.h"

f64 sqrt(f64 x) { (void)x; }

f64 pow(f64 x, f64 y) {
  if (y == 1.0)
    return x;
  if (y == 2.0)
    return x * x;
  if (y == -1.0)
    return 1.0 / x;
  if (y == 0)
    return 1.0;

  f64 res = x;
  for (u32 i = 0; i < y; ++i) {
    res *= x;
  }

  return res;
}

f64 expf(f64 x) { return pow(euler_f64, x); }

f64 sigmoidf(f64 x) { return 1.0 / (1.0 + expf(-x)); }
