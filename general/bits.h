#ifndef BITS_H
#define BITS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define PeekBit(x, n) ((x) & (1 << (n))) >> (n)
#define SetBit(x, n) (x) | (1 << (n))
#define UnsetBit(x, n) (x) & ~(1 << (n))
#define ToggleBit(x, n) (x) ^ (1 << (n))

typedef u8 byte;
typedef u16 word;
typedef u32 dword;
typedef u64 qword;

#ifdef __cplusplus
}
#endif

#endif // BITS_H