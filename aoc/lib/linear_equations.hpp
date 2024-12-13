#ifndef LINEAR_EQUATIONS_HPP
#define LINEAR_EQUATIONS_HPP

#ifndef MATRIX_HPP
#include "matrix.hpp"
#warning "Please include matrix.hpp before linear_equations.hpp"
#endif

using namespace std;

template <typename T, typename U, size_t ROWS, size_t COLS,
          typename enable_if<is_convertible_v<T, double>, bool>::type = true,
          typename enable_if<is_convertible_v<U, double>, bool>::type = true>
pair<Vector<double, COLS>, int> solveLinear(Matrix<T, ROWS, COLS> &matrix,
                                            Vector<U, COLS> &target) {
  Matrix<double, ROWS, COLS> A(matrix);
  Vector<double, COLS> b(target);
  constexpr const size_t n = ROWS, m = COLS;
  int rank = 0, br, bc;
  vector<int> col(m);
  Vector<double, COLS> x(0);
  iota(col.begin(), col.end(), 0);

  for (size_t i = 0; i < n; ++i) {
    double v, bv = 0;
    for (size_t r = i; r < n; ++r) {
      for (size_t c = i; c < m; ++c) {
        v = fabs(A[r][c]);
        if (v > bv)
          br = r, bc = c, bv = v;
      }
    }
    if (bv <= _MATRIX_EPS) {
      for (size_t j = i; j < n; ++j)
        if (fabs(b[j]) > _MATRIX_EPS)
          return {x, -1};
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    for (size_t j = 0; j < n; ++j)
      swap(A[j][i], A[j][bc]);
    bv = 1 / A[i][i];
    for (size_t j = i + 1; j < n; ++j) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      for (size_t k = i + 1; k < m; ++k)
        A[j][k] -= fac * A[i][k];
    }
    rank++;
  }

  for (int i = rank; i--;) {
    b[i] /= A[i][i];
    x[col[i]] = b[i];
    for (int j = 0; j < i; ++j)
      b[j] -= A[j][i] * b[i];
  }
  return {x, rank}; // (multiple solutions if rank < m)
}

#endif