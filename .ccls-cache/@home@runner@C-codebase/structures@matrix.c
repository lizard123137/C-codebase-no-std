#include "matrix.h"

Mat mat_alloc(u32 rows, u32 cols) {
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.stride = cols;
  m.es = heap_alloc(sizeof(m.es) * rows * cols);
  return m;
}

void mat_sum(Mat a, Mat b) {
  Assert(a.rows == b.rows && a.cols == b.cols);
  for (u32 i = 0; i < a.rows; ++i) {
    for (u32 j = 0; j < a.cols; ++j) {
      MatAt(a, i, j) += MatAt(b, i, j);
    }
  }
}

void mat_rand(Mat m) {
  for (u32 i = 0; i < m.rows; ++i) {
    for (u32 j = 0; j < m.cols; ++j) {
      MatAt(m, i, j) = rand_double();
    }
  }
}

void mat_fill(Mat m, f64 x) {
  for (u32 i = 0; i < m.rows; ++i) {
    for (u32 j = 0; j < m.cols; ++j) {
      MatAt(m, i, j) = x;
    }
  }
}

void mat_print(Mat m) {
  for (u32 i = 0; i < m.rows; ++i) {
    for (u32 j = 0; j < m.cols; ++j) {
      printf("%lf ", MatAt(m, i, j));
    }
    putchar('\n');
  }
}