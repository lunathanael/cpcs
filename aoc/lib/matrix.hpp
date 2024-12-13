#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <cassert>

using namespace std;

template<class T, int N> struct Matrix {
	array<array<T, N>, N> data;

	Matrix operator*(const Matrix& m) const {
		Matrix ret;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				for (int k = 0; k < N; ++k) {
					ret.data[i][j] += data[i][k] * m.data[k][j];
				}
			}
		}
		return ret;
	}

	array<T, N> operator*(const array<T, N>& vec) const {
		array<T, N> ret{};
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				ret[i] += data[i][j] * vec[j];
			}
		}
		return ret;
	}
	Matrix operator^(long long p) const {
		assert(p >= 0);
		Matrix a, b(*this); 
		for (int i = 0; i < N; ++i) {
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
};

#endif