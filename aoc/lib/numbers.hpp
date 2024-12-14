#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <array>
#include <cmath>
#include <vector>

using namespace std;

/**
 * Author: Noam527
 * License: CC0
 * Source: folklore
 */
static constexpr const long long MOD1e9_7 = 1000000007; // faster if const
static constexpr const double EPS = 1e-9;

template <typename T, enable_if_t<is_same_v<T, double>, bool> = true>
constexpr bool is_int(const T d) {
  return fabs(d - round(d)) < EPS;
}

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

/**
 * Author: chilli, SJTU, pajenegod
 * License: CC0
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
 * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
 * Time: $O(n^{1/4})$, less for numbers with small factors.
 * Status: stress-tested
 *
 * Details: This implementation uses the improvement described here
 * (https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants), where
 * one can accumulate gcd calls by some factor (40 chosen here through
 * exhaustive testing). This improves performance by approximately 6-10x
 * depending on the inputs and speed of gcd. Benchmark found here:
 * (https://ideone.com/nGGD9T)
 *
 * GCD can be improved by a factor of 1.75x using Binary GCD
 * (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).
 * However, with the gcd accumulation the bottleneck moves from the gcd calls
 * to the modmul. As GCD only constitutes ~12% of runtime, speeding it up
 * doesn't matter so much.
 *
 * This code can probably be sped up by using a faster mod mul - potentially
 * montgomery reduction on 128 bit integers.
 * Alternatively, one can use a quadratic sieve for an asymptotic improvement,
 * which starts being faster in practice around 1e13.
 *
 * Brent's cycle finding algorithm was tested, but doesn't reduce modmul calls
 * significantly.
 *
 * Subtle implementation notes:
 * - prd starts off as 2 to handle the case n = 4; it's harmless for other n
 *   since we're guaranteed that n > 2. (Pollard rho has problems with prime
 *   powers in general, but all larger ones happen to work.)
 * - t starts off as 30 to make the first gcd check come earlier, as an
 *   optimization for small numbers.
 * - we vary f between restarts because the cycle finding algorithm does not
 *   find the first element in the cycle but rather one at distance k*|cycle|
 *   from the start, and that can result in continual failures if all cycles
 *   have the same size for all prime factors. E.g. fixing f(x) = x^2 + 1 would
 *   loop infinitely for n = 352523 * 352817, where all cycles have size 821.
 * - we operate on residues in [i, n + i) which modmul is not designed to
 *   handle, but specifically modmul(x, x) still turns out to work for small
 *   enough i. (With reference to the proof in modmul-proof.tex, the argument
 *   for "S is in [-c, 2c)" goes through unchanged, while S < 2^63 now follows
 *   from S < 2c and S = x^2 (mod c) together implying S < c + i^2.)
 */
// unsigned long long pollard(unsigned long long n) {
//   unsigned long long x = 0, y = 0, t = 30, prd = 2, i = 1, q;
//   auto f = [&](unsigned long long x) { return modmul(x, x, n) + i; };
//   while (t++ % 40 || __gcd(prd, n) == 1) {
//     if (x == y)
//       x = ++i, y = f(x);
//     if ((q = modmul(prd, max(x, y) - min(x, y), n)))
//       prd = q;
//     x = f(x), y = f(f(y));
//   }
//   return __gcd(prd, n);
// }
// vector<unsigned long long> factor(unsigned long long n) {
//   if (n == 1)
//     return {};
//   if (isPrime(n))
//     return {n};
//   ull x = pollard(n);
//   auto l = factor(x), r = factor(n / x);
//   l.insert(l.end(), all(r));
//   return l;
// }

#endif
