#ifndef IO_H
#define IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "args.h"
#include "base.h"

void printf(u8 *format, ...);
void puts(u8 *str);
void putchar(u8 c);

#ifdef __cplusplus
}
#endif

#endif // IO_H