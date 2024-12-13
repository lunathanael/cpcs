#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

static constexpr const double _MATRIX_EPS = 1e-12;

template <class T, size_t N> struct Vector : array<T, N> {

  constexpr Vector(const T val = T{}) { this->fill(val); }

    template <typename OT, typename ENABLE = enable_if<!is_same_v<T, OT>, OT>>
  constexpr Vector(const Vector<OT, N> &m) {
    for (size_t i = 0; i < N; ++i) {
      (*this)[i] = static_cast<T>(m[i]);
    }
  }

  constexpr T operator*(const Vector<T, N> &m) const {
    T ret = 0;
    for (int i = 0; i < N; ++i) {
      ret += (*this)[i] * m[i];
    }
    return ret;
  }

  constexpr Vector operator*(const T val) const {
    Vector<T, N> ret;
    for (int i = 0; i < N; ++i) {
      ret[i] = (*this)[i] * val;
    }
    return ret;
  }

  constexpr Vector operator+(const Vector &v) const {
    Vector<T, N> ret;
    for (int i = 0; i < N; ++i) {
      ret[i] = (*this)[i] + v[i];
    }
    return ret;
  }
};

template <class T, size_t ROWS, size_t COLS> struct Matrix {
  Vector<Vector<T, COLS>, ROWS> data;

  constexpr Matrix(T val = T{}) : data{Vector<T, COLS>(val)} {}

  template <typename OT, typename ENABLE = enable_if<!is_same_v<T, OT>, OT>>
  constexpr Matrix(const Matrix<OT, ROWS, COLS> &m) {
    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        data[i][j] = static_cast<T>(m.data[i][j]);
      }
    }
  }

  static constexpr size_t size() { return ROWS; }

  template <typename OT, size_t OCOLS>
  constexpr Matrix<T, ROWS, OCOLS>
  operator*(const Matrix<OT, COLS, OCOLS> &m) const {
    Matrix<T, ROWS, OCOLS> ret(0);
    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < OCOLS; ++j) {
        for (size_t k = 0; k < COLS; ++k) {
          ret.data[i][j] += data[i][k] * m.data[k][j];
        }
      }
    }
    return ret;
  }

  template <typename OT>
  constexpr Vector<T, ROWS> operator*(const Vector<OT, COLS> &vec) const {
    Vector<T, ROWS> ret;
    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        ret[i] += data[i][j] * vec[j];
      }
    }
    return ret;
  }

  constexpr Matrix<T, ROWS, COLS> operator*(const T val) const {
    Matrix<T, ROWS, COLS> ret;
    for (size_t i = 0; i < ROWS; ++i) {
      ret.data[i] = data[i] * val;
    }
    return ret;
  }

  template <typename OT>
  constexpr Matrix<T, ROWS, COLS>
  operator+(const Matrix<OT, ROWS, COLS> &m) const {
    Matrix<T, ROWS, COLS> ret;
    for (size_t i = 0; i < ROWS; ++i) {
      ret.data[i] = data[i] + m.data[i];
    }
    return ret;
  }

  constexpr Matrix operator^(long long p) const {
    assert(p >= 0);
    Matrix a, b(*this);
    for (size_t i = 0; i < ROWS; ++i) {
      a.data[i][i] = 1;
    }
    while (p) {
      if (p & 1) {
        a = a * b;
      }
      b = b * b;
      p >>= 1;
    }
    return a;
  }

  /**
   * Author: Simon Lindholm
   * Source: folklore
   * Description: Calculates determinant of a matrix. Destroys the matrix.
   * Time: O(N^3)
   */
  template <typename enable_if<ROWS == COLS && is_convertible_v<T, double>,
                               bool>::type = true>
  constexpr double det() const {
    double res = 1;
    Matrix<double, ROWS, COLS> a(*this);
    for (size_t i = 0; i < ROWS; ++i) {
      size_t b = i;
      for (size_t j = i + 1; j < ROWS; ++j) {
        if (fabs(a[j][i]) > fabs(a[b][i]))
          b = j;
      }
      if (i != b) {
        swap(a[i], a[b]);
        res *= -1;
      }
      res *= a[i][i];
      if (res == 0)
        return 0;
      for (size_t j = i + 1; j < ROWS; ++j) {
        double v = a[j][i] / a[i][i];
        if (v != 0) {
          for (size_t k = i + 1; k < ROWS; ++k) {
            a[j][k] -= v * a[i][k];
          }
        }
      }
    }
    return res;
  }

  /**
   * Author: Max Bennedich
   * Description: Invert matrix A. Returns {inv(A), rank}.
   * Time: O(N^3)
   */
  template <typename enable_if<ROWS == COLS, bool>::type = true,
            typename enable_if<is_convertible_v<T, double>, bool>::type = true>
  constexpr pair<Matrix<double, ROWS, COLS>, int> inverse() const {
    constexpr const int N = ROWS;

    Matrix<double, N, N> A(*this);
    vector<int> col(N);
    Matrix<double, N, N> tmp(0);
    for (size_t i = 0; i < N; ++i) {
      tmp[i][i] = 1;
      col[i] = i;
    }

    for (int i = 0; i < N; ++i) {
      int r = i, c = i;
      for (int j = i; j < N; ++j) {
        for (int k = i; k < N; ++k) {
          if (fabs(A[j][k]) > fabs(A[r][c]))
            r = j, c = k;
        }
      }
      if (fabs(A[r][c]) < _MATRIX_EPS)
        return {A, i};
      A[i].swap(A[r]);
      tmp[i].swap(tmp[r]);
      for (int j = 0; j < N; ++j)
        swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
      swap(col[i], col[c]);
      double v = A[i][i];
      for (int j = i + 1; j < N; ++j) {
        double f = A[j][i] / v;
        A[j][i] = 0;
        for (int k = i + 1; k < N; ++k)
          A[j][k] -= f * A[i][k];
        for (int k = 0; k < N; ++k)
          tmp[j][k] -= f * tmp[i][k];
      }
      for (int j = i + 1; j < N; ++j)
        A[i][j] /= v;
      for (int j = 0; j < N; ++j)
        tmp[i][j] /= v;
      A[i][i] = 1;
    }

    /// forget A at this point, just eliminate tmp backward
    for (int i = N - 1; i > 0; --i) {
      for (int j = 0; j < i; ++j) {
        double v = A[j][i];
        for (int k = 0; k < N; ++k)
          tmp[j][k] -= v * tmp[i][k];
      }
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        A[col[i]][col[j]] = tmp[i][j];
      }
    }
    return {A, N};
  }

  constexpr Matrix<T, COLS, ROWS> transpose() const {
    Matrix<T, COLS, ROWS> ret;
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        ret.data[j][i] = data[i][j];
      }
    }
    return ret;
  }

  constexpr Vector<T, COLS> &operator[](const int i) { return data[i]; }
  constexpr const Vector<T, COLS> &operator[](const int i) const {
    return data[i];
  }

  friend ostream &operator<<(ostream &os, const Matrix<T, ROWS, COLS> &m) {
    for (size_t i = 0; i < ROWS; ++i) {
      os << m.data[i] << '\n';
    }
    return os;
  }
};

#endif