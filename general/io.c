#include "io.h"

#define PRINTF_BUFFER_SIZE 64
#define PRINTF_DECIMAL_POINT 1000

#define PRINTF_STATE_NORMAL 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_LENGTH_SHORT 2
#define PRINTF_STATE_LENGTH_LONG 3
#define PRINTF_STATE_SPEC 4

#define PRINTF_LENGTH_DEFAULT 0
#define PRINTF_LENGTH_SHORT_SHORT 1
#define PRINTF_LENGTH_SHORT 2
#define PRINTF_LENGTH_LONG_LONG 3
#define PRINTF_LENGTH_LONG 4

const u8 g_HexChars[] = "0123456789abcdef";

i32 *printf_number(i32 *argp, i32 length, bool sign, i32 radix) {
  u8 buffer[PRINTF_BUFFER_SIZE] = {0};
  u128 number;
  i32 number_sign = 1;
  i32 pos = 0;

  switch (length) {
  case PRINTF_LENGTH_SHORT_SHORT:
  case PRINTF_LENGTH_SHORT:
  case PRINTF_LENGTH_DEFAULT:
    if (sign) {
      i32 n = *argp;
      if (n < 0) {
        n = -n;
        number_sign = -1;
      }
      number = (u128)n;
    } else
      number = *(u64 *)argp;
    argp++;
    break;

  case PRINTF_LENGTH_LONG:
    if (sign) {
      i64 n = *(i64 *)argp;
      if (n < 0) {
        n = -n;
        number_sign = -1;
      }
      number = (u128)n;
    } else
      number = *(u64 *)argp;
    argp += 2;
    break;

  case PRINTF_LENGTH_LONG_LONG:
    if (sign) {
      i128 n = *(i128 *)argp;
      if (n < 0) {
        n = -n;
        number_sign = -1;
      }
      number = (u128)n;
    } else
      number = *(u128 *)argp;
    argp += 4;
    break;
  }

  do {
    u32 rem = number % radix;
    number /= radix;
    buffer[pos++] = g_HexChars[rem];
  } while (number > 0);

  if (sign && number_sign < 0)
    buffer[pos++] = '-';

  while (--pos >= 0)
    putchar(buffer[pos]);

  return argp;
}

i32 *printf_fract(i32 *argp, i32 length) {
  u8 buffer[PRINTF_BUFFER_SIZE] = {0};
  u16 decimals = {0};
  i32 units = {0};
  i32 pos = {0};
  i32 number_sign = 1;

  if (length == PRINTF_LENGTH_LONG) {
    f64 f64_val = *(f64 *)argp;
    if (f64_val < 0)
      number_sign = -1;

    if (number_sign < 0) {
      decimals = (i32)(f64_val * -PRINTF_DECIMAL_POINT) % PRINTF_DECIMAL_POINT;
      units = (i32)(-1 * f64_val);
    } else {
      decimals = (i32)(f64_val * PRINTF_DECIMAL_POINT) % PRINTF_DECIMAL_POINT;
      units = (i32)f64_val;
    }

    argp += 2;
  } else {
    f32 f32_val = *(f32 *)argp;
    if (f32_val < 0)
      number_sign = -1;

    if (number_sign < 0) {
      decimals = (i32)(f32_val * -PRINTF_DECIMAL_POINT) % PRINTF_DECIMAL_POINT;
      units = (i32)(-1 * f32_val);
    } else {
      decimals = (i32)(f32_val * PRINTF_DECIMAL_POINT) % PRINTF_DECIMAL_POINT;
      units = (i32)f32_val;
    }

    argp++;
  }

  buffer[pos++] = (decimals % 10) + '0';
  decimals /= 10;
  buffer[pos++] = (decimals % 10) + '0';
  decimals /= 10;
  buffer[pos++] = (decimals % 10) + '0';
  buffer[pos++] = '.';

  if (units == 0)
    buffer[pos++] = '0';
  while (units > 0) {
    buffer[pos++] = (units % 10) + '0';
    units /= 10;
  }

  if (number_sign < 0)
    buffer[pos++] = '-';

  while (--pos >= 0)
    putchar(buffer[pos]);

  return argp;
}

void printf(u8 *format, ...) {
  i32 state = PRINTF_STATE_NORMAL;
  i32 length = PRINTF_LENGTH_DEFAULT;
  i32 radix = 10;
  bool sign = false;

  i32 *argp = (i32 *)&format;
  argp++;

  while (*format) {
    switch (state) {
    case PRINTF_STATE_NORMAL:
      switch (*format) {
      case '%':
        state = PRINTF_STATE_LENGTH;
        break;
      default:
        putchar(*format);
        break;
      }
      break;

    case PRINTF_STATE_LENGTH:
      switch (*format) {
      case 'h':
        length = PRINTF_LENGTH_SHORT;
        break;
      case 'l':
        length = PRINTF_LENGTH_LONG;
        break;
      default:
        goto PRINTF_STATE_SPEC_;
      }
      break;

    case PRINTF_STATE_LENGTH_SHORT:
      switch (*format) {
      case 'h':
        length = PRINTF_LENGTH_SHORT_SHORT;
        state = PRINTF_STATE_SPEC;
        break;
      default:
        goto PRINTF_STATE_SPEC_;
      }
      break;

    case PRINTF_STATE_LENGTH_LONG:
      switch (*format) {
      case 'l':
        length = PRINTF_LENGTH_LONG_LONG;
        state = PRINTF_STATE_SPEC;
        break;
      default:
        goto PRINTF_STATE_SPEC_;
      }
      break;

    case PRINTF_STATE_SPEC:
    PRINTF_STATE_SPEC_:
      switch (*format) {
      case 'c':
        putchar((char)*argp);
        argp++;
        break;

      case 's':
        puts(*(u8 **)argp);
        argp++;
        break;

      case '%':
        putchar('%');
        break;

      case 'd':
      case 'i':
        radix = 10;
        sign = true;
        argp = printf_number(argp, length, sign, radix);
        break;

      case 'u':
        radix = 10;
        sign = false;
        argp = printf_number(argp, length, sign, radix);
        break;

      case 'X':
      case 'x':
      case 'p':
        radix = 16;
        sign = false;
        argp = printf_number(argp, length, sign, radix);
        break;

      case 'o':
        radix = 8;
        sign = false;
        argp = printf_number(argp, length, sign, radix);
        break;

      case 'f':
        argp = printf_fract(argp, length);

      default:
        break;
      }

      state = PRINTF_STATE_NORMAL;
      length = PRINTF_LENGTH_DEFAULT;
      radix = 10;
      sign = false;
      break;
    }
    format++;
  }
}

void puts(u8 *str) {
  i32 idx = 0;
  do {
    putchar(str[idx++]);
  } while (str[idx] != '\0');
}

void putchar(u8 c) {
#if defined(ARCH_X86)
  i32 dword_char;
  dword_char = (i32)c;
  asm volatile(".intel_syntax noprefix;"
               "mov r10,rsp;"  // save rsp.
               "sub rsp,8;"    // space for buffer, align by 8.
               "mov [rsp],al;" // store the character into buffer.
               "mov edi,1;"    // STDOUT.
               "mov rsi,rsp;"  // pointer to buffer.
               "mov edx,1;"    // string length in bytes.
               "mov eax,1;"    // WRITE.
               "syscall;"      // clobbers rcx & r11.
               "mov rsp,r10;"  // restore rsp.
               ".att_syntax prefix;"
               /* outputs */
               :
               /* inputs: eax */
               : "a"(dword_char)
               /* clobbered regs */
               : "rcx", "rdx", "rsi", "rdi", "r10", "r11");
#else
#error "PUTCHAR NOT IMPLEMENTED FOR OTHER ARCHITECTURES"
#endif
}