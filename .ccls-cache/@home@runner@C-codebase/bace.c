#include "base.h"

u32 hash(u32 state) {
  state ^= 2747636419u;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  return state;
}

u32 strnlen(u8 *name, u32 max_len) {
  u32 cnt = 0;
  while (name[cnt] != '\0')
    cnt++;
  return cnt;
}