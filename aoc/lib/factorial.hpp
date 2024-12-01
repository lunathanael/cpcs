#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <array>
#include <cstdint>
#include <iostream>

using namespace std;

static const constexpr array<uint64_t, 21> _FACTORIALS_ARR = []() {
  array<uint64_t, 21> factorials = {1, 1};
  for (unsigned int i = 2; i <= 20; ++i) {
    factorials[i] = factorials[i - 1] * i;
  };
  return factorials;
}();

#define factorial(n) _FACTORIALS_ARR[n]

#endif // FACTORIAL_HPP
