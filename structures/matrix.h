#ifndef MATRIX_H
#define MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../general/base.h"
#include "../general/io.h"
#include "../general/memory.h"

typedef struct {
  u32 rows;
  u32 cols;
  u32 stride;
  f64 *es;
} Mat;

#define MatAt(mat, row, col) (mat).es[((row) * (mat).stride) + (col)]

Mat mat_alloc(u32 rows, u32 cols);
void mat_sum(Mat a, Mat b);
void mat_rand(Mat m);
void mat_fill(Mat m, f64 x);
void mat_print(Mat m);

#ifdef __cplusplus
}
#endif

#endif // MATRIX_H