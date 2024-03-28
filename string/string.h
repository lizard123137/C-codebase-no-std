#ifndef STRING_H
#define STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../general/base.h"

u32 strcmp(u8 *str1, u8 *str2);
u32 strlen(u8 *str);

u32 strncmp(u8 *str1, u8 *str2, u32 len);
u32 strnlen(u8 *str, u32 max_len);

#ifdef __cplusplus
}
#endif

#endif // STRING_H