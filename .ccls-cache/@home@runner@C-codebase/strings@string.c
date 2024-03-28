#include "string.h"

u32 strcmp(u8 *str1, u8 *str2) {
  if (strlen(str1) != strlen(str2))
    return 1;

  u32 index = 0;
  while (str1[index] != '\0') {
    if (str1[index] != str2[index])
      return 1;
    index++;
  }
  return 0;
}

u32 strlen(u8 *str) {
  u32 cnt = 0;
  while (str[cnt] != '\0')
    cnt++;
  return cnt;
}

u32 strncmp(u8 *str1, u8 *str2, u32 len) {
  if (strlen(str1) != strlen(str2) && strlen(str1) < len)
    return 1;

  u32 index = 0;
  while (index < len) {
    if (str1[index] != str2[index])
      return 1;
    index++;
  }
  return 0;
}

u32 strnlen(u8 *str, u32 max_len) {
  u32 cnt = 0;
  while (str[cnt] != '\0' && cnt < max_len)
    cnt++;
  return cnt;
}