#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <array>

using namespace std;

/**
 * Author: Noam527
 * License: CC0
 * Source: folklore
 */
static constexpr const long long MOD1e9_7 = 1000000007; // faster if const

constexpr long long modpow(long long b, long long e) {
  long long ans = 1;
  for (; e != 0; b = (b * b) % MOD1e9_7, e >>= 1) {
    if ((e & 1) != 0) {
      ans = ans * b % MOD1e9_7;
    }
  }
  return ans;
}

/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * License: CC0
 * Source:
 * https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate a * b mod c (or a^b mod c) for 0 <= a,b <= c <= 7.2 *
 * 10^18.
 * Time: O(1) for modmul, O(log b) for modpow
 * Details: Runs ~2x faster than naive (__int128_t)a * b % M. Assumes long
 * doubles are x87 80-bit floats. For 64-bit long doubles (e.g. MSVC), only
 * valid for 0 <= a,b <= c < 2^52 ≈ 4.5 * 10^15.
 */
constexpr unsigned long long modmul(unsigned long long a, unsigned long long b,
                                    unsigned long long M) {
  long long ret = a * b - M * static_cast<unsigned long long>(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= static_cast<long long>(M));
}

constexpr unsigned long long modpow(unsigned long long b, unsigned long long e,
                                    unsigned long long mod) {
  unsigned long long ans = 1;
  for (; e != 0; b = modmul(b, b, mod), e >>= 1) {
    if ((e & 1) != 0) {
      ans = modmul(ans, b, mod);
    }
  }
  return ans;
}

/**
 * Author: chilli, c1729, Simon Lindholm
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Deterministic Miller-Rabin primality test.
 * Guaranteed to work for numbers up to 7 \cdot 10^{18}; for larger numbers,
 * use Python and extend A randomly.
 * Time: 7 times the complexity of a^b mod c.
 */

static constexpr const array<unsigned long long, 7> _NUMBERS_PRIME_A = {
    2, 325, 9375, 28178, 450775, 9780504, 1795265022};

constexpr bool is_prime(unsigned long long n) {
  if (n < 2 || (n % 6 % 4) != 1) {
    return (n | 1) == 3;
  }
  unsigned long long s = __builtin_ctzll(n - 1);
  unsigned long long d = n >> s;
  for (const unsigned long long a :
       _NUMBERS_PRIME_A) { // ^ count trailing zeroes
    unsigned long long p = modpow(a % n, d, n);
    unsigned long long i = s;
    while (p != 1 && p != n - 1 && a % n && i--) {
      p = modmul(p, p, n);
    }
    if (p != n - 1 && i != s) {
      return false;
    }
  }
  return true;
}

#endif
