#ifndef MATH_H
#define MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../general/base.h"

#define Rad2Deg(x) ((x) / PI * 180)
#define Deg2Rad(x) ((x)*PI / 180)

static f32 machine_epsilon_f32 = 1.1920929e-7f;
static f32 euler_f32 = 2.71828182845f;
static f32 pi_f32 = 3.14159265359f;
static f32 tau_f32 = 6.28318530718f;

static f64 machine_epsilon_f64 = 2.220446e-16;
static f64 euler_f64 = 2.71828182845;
static f64 pi_f64 = 3.14159265359;
static f64 tau_f64 = 6.28318530718;

f64 sqrt(f64 x);
f64 pow(f64 x, f64 y);
f64 expf(f64 x);
f64 sigmoidf(f64 x);

#ifdef __cplusplus
}
#endif

#endif // MATH_H