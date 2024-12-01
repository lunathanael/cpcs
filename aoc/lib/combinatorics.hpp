#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

static const constexpr array<uint64_t, 21> _FACTORIALS_ARR = []() {
  array<uint64_t, 21> factorials = {1, 1};
  for (unsigned int i = 2; i <= 20; ++i) {
    factorials[i] = factorials[i - 1] * i;
  };
  return factorials;
}();

static const constexpr array<double, 151> _FACTORIALS_ARR_DOUBLE = []() {
  array<double, 151> factorials = {1, 1};
  for (unsigned int i = 2; i <= 150; ++i) {
    factorials[i] = factorials[i - 1] * i;
  };
  return factorials;
}();

#define factorial(n) _FACTORIALS_ARR[n]
#define factoriald(n) _FACTORIALS_ARR_DOUBLE[n]

/**
 * Author: Mattias de Zalenski, Fredrik Niemelä, Per Austrin, Simon Lindholm
 * Date: 2002-09-26
 * Source: Max Bennedich
 * Description: Computes binomal
 * (k_1 + ... + k_n)(k_1, k_2, ..., k_n)
 * = (k_1 + ... + k_n)! / (k_1!k_2!...k_n!)
 * */
// Calculating multinomial coefficients
// Represents the number of ways to assign sum(v) objects to size(v) groups
uint64_t multinomial(vector<int> &v) {
  uint64_t c = 1, m = v.empty() ? 1 : v[0];
  for (int i = 1; i < static_cast<int>(v.size()); ++i) {
    for (int j = 0; j < v[i]; ++j) {
      c = c * ++m / (j + 1);
    }
  }
  return c;
}

/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Permutation -> integer conversion. (Not order preserving.)
 * Integer -> permutation can use a lookup table.
 * Time: O(n)
 * perm_to_int: Safe for n <= 12
 * perm_to_intll: Safe for n <= 20
 */
int perm_to_int(const vector<int> &v) {
  int use = 0, i = 0, r = 0;
  for (int x : v)
    r = r * ++i + __builtin_popcount(use & -(1 << x)),
    use |= 1 << x; // (note: minus, not ~!)
  return r;
}

int64_t perm_to_intll(const vector<int> &v) {
  int64_t use = 0, i = 0, r = 0;
  for (int x : v)
    r = r * ++i + __builtin_popcountll(use & -(1LL << x)),
    use |= 1LL << x; // (note: minus, not ~!)
  return r;
}

#endif