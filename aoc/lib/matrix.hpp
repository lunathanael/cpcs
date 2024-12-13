#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <cassert>
#include <iostream>

using namespace std;

template <class T, int N> struct Vector : array<T, N> {
  constexpr Vector(const T val = T{}) { this->fill(val); }
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

template <class T, int ROWS, int COLS> struct Matrix {
  Vector<Vector<T, COLS>, ROWS> data;

  constexpr Matrix(T val = T{}) : data{Vector<T, COLS>(val)} {}

  template <typename OT, typename ENABLE = enable_if<!is_same_v<T, OT>, OT>>
  constexpr Matrix(const Matrix<OT, ROWS, COLS> &m) {
	for (int i = 0; i < ROWS; ++i) {
	  for (int j = 0; j < COLS; ++j) {
		data[i][j] = static_cast<T>(m.data[i][j]);
	  }
	}
  }

  template <typename OT, int OCOLS>
  constexpr Matrix<T, ROWS, OCOLS>
  operator*(const Matrix<OT, COLS, OCOLS> &m) const {
	Matrix<T, ROWS, OCOLS> ret(0);
	for (int i = 0; i < ROWS; ++i) {
	  for (int j = 0; j < OCOLS; ++j) {
		for (int k = 0; k < COLS; ++k) {
		  ret.data[i][j] += data[i][k] * m.data[k][j];
		}
	  }
	}
	return ret;
  }

  template <typename OT>
  constexpr Vector<T, ROWS> operator*(const Vector<OT, COLS> &vec) const {
	Vector<T, ROWS> ret;
	for (int i = 0; i < ROWS; ++i) {
	  for (int j = 0; j < COLS; ++j) {
		ret[i] += data[i][j] * vec[j];
	  }
	}
	return ret;
  }

  constexpr Matrix<T, ROWS, COLS> operator*(const T val) const {
	Matrix<T, ROWS, COLS> ret;
	for (int i = 0; i < ROWS; ++i) {
	  ret.data[i] = data[i] * val;
	}
	return ret;
  }

  template <typename OT>
  constexpr Matrix<T, ROWS, COLS>
  operator+(const Matrix<OT, ROWS, COLS> &m) const {
	Matrix<T, ROWS, COLS> ret;
	for (int i = 0; i < ROWS; ++i) {
	  ret.data[i] = data[i] + m.data[i];
	}
	return ret;
  }

  constexpr Matrix operator^(long long p) const {
	assert(p >= 0);
	Matrix a, b(*this);
	for (int i = 0; i < ROWS; ++i) {
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

  constexpr Vector<T, COLS> &operator[](const int i) { return data[i]; }
  constexpr const Vector<T, COLS> &operator[](const int i) const {
	return data[i];
  }

  friend ostream &operator<<(ostream &os, const Matrix<T, ROWS, COLS> &m) {
	for (int i = 0; i < ROWS; ++i) {
	  os << m.data[i] << '\n';
	}
	return os;
  }
};

#endif