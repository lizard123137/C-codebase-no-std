#ifndef BASE_H
#define BASE_H

// This is an educational project designed to learn about the inner workings of
// stdlib.c by implementing its functionality from scratch
// using simple and readable methods

// This software is dual-licensed to the public domain and under the following
// license: you are granted a perpetual, irrevocable license to copy, modify,
// publish, and distribute this file as you see fit.

#ifdef __cplusplus
extern "C" {
#endif

// Context cracking
#if defined(__clang__)
#define COMPILER_CLANG 1

#if defined(_WIN32)
#define OS_WINDOWS 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#else
#error missing OS detection
#endif

#if defined(__amd64__)
#define ARCH_X64 1
#elif defined(__i386__)
#define ARCH_X86 1
#elif defined(__arm__)
#define ARCH_ARM 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#else
#error missing arch detection
#endif

#elif defined(_MSC_VER)
#define COMPILER_CL 1

#if defined(_WIN32)
#define OS_WINDOWS 1
#else
#error missing OS detection
#endif

#if defined(_M_AMD64)
#define ARCH_X64 1
#elif defined(_M_I86)
#define ARCH_X86 1
#elif defined(_M_ARM)
#define ARCH_ARM 1
#else
#error missing arch detection
#endif

#elif defined(__GNUC__)
#define COMPILER_GCC 1

#if defined(_WIN32)
#define OS_WINDOWS 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#else
#error missing OS detection
#endif

#if defined(__amd64__)
#define ARCH_X64 1
#elif defined(__i386__)
#define ARCH_X86 1
#elif defined(__arm__)
#define ARCH_ARM 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#else
#error missing arch detection
#endif

#else
#error no context cracking for this compiler
#endif

// Zero fill missing context macros
#if !defined(COMPILER_CL)
#define COMPILER_CL 0
#endif
#if !defined(COMPILER_CLANG)
#define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_GCC)
#define COMPILER_GCC 0
#endif

#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif
#if !defined(OS_MAC)
#define OS_MAC 0
#endif

#if !defined(ARCH_X64)
#define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
#define ARCH_X86 0
#endif
#if !defined(ARCH_ARM)
#define ARCH_ARM 0
#endif
#if !defined(ARCH_ARM64)
#define ARCH_ARM64 0
#endif

#if !defined(ENABLE_ASSERT)
#define ENABLE_ASSERT 0
#endif

// Helpful macros
#define NULL ((void *)0)

#define Stmnt(S)                                                               \
  do {                                                                         \
    S                                                                          \
  } while (0)

#if !defined(AssertBreak)
#define AssertBreak() (((*int)0) = 0)
#endif

#if ENABLE_ASSERT
#define Assert(c) Stmnt(if (!(c)) { AssertBreak(); })
#else
#define Assert(c)
#endif

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A, B) A##B
#define Glue(A, B) Glue_(A, B)

#define ArrayCount(a) (sizeof(a) / sizeof(*(a)))

#define IntFromPtr(p) (unsigned long long)((char *)p - (char *)0)
#define PtrFromInt(n) (void *)((char *)0 + (n))

#define Member(T, m) (((T *)0)->m)
#define OffsetOfMember(T, m) IntFromPtr(&Member(T, m))

#define Abs(x) (((x) < 0) ? -(x) : (x))

#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))
#define Clamp(a, x, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) : (x))
#define ClampTop(a, b) Min(a, b)
#define ClampBot(a, b) Max(a, b)

#ifdef __cplusplus
#define EXTERN_C_START extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_START
#define EXTERN_C_END
#endif

// Basic types
#define TRUE 1
#define FALSE 0

typedef signed char i8;
typedef signed short int i16;
typedef signed int i32;
typedef signed long int i64;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long int u64;

typedef i8 b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

typedef float f32;
typedef double f64;

// Basic constants
static i8 min_i8 = (i8)0x80;
static i16 min_i16 = (i16)0x8000;
static i32 min_i32 = (i32)0x80000000;
static i64 min_i64 = (i64)0x8000000000000000llu;

static i8 max_i8 = (i8)0x7f;
static i16 max_i16 = (i16)0x7fff;
static i32 max_i32 = (i32)0x7fffffff;
static i64 max_i64 = (i64)0x7fffffffffffffffllu;

static u8 max_u8 = (i8)0xff;
static u16 max_u16 = (i16)0xffff;
static u32 max_u32 = (i32)0xffffffff;
static u64 max_u64 = (i64)0xffffffffffffffffllu;

// Symbolic constants

enum Axis { Axis_X, Axis_Y, Axis_Z, Axis_W };

enum Month {
  Month_Jan,
  Month_Feb,
  Month_Mar,
  Month_Apr,
  Month_May,
  Month_Jun,
  Month_Jul,
  Month_Aug,
  Month_Sep,
  Month_Oct,
  Month_Nov,
  Month_Dec
};

enum Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

// Helpful functions
u32 hash(u32 state);
u32 getTime(void);
u32 rand();
f64 rand_double();

#ifdef __cplusplus
}
#endif

#endif // BASE_H