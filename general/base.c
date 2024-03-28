#include "base.h"

static u32 seed = 1;

u32 hash(u32 state) {
  state ^= 2747636419u;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  return state;
}

u32 rand() {
  u32 temp = hash(seed);
  seed = temp;
  return temp;
}

f64 rand_double(u32 *seed) { return (double)rand(seed) / (double)max_u32; }