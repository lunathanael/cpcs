/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Permutation -> integer conversion. (Not order preserving.)
 * Integer -> permutation can use a lookup table.
 * Time: O(n)
 * perm_to_int: Safe for n <= 12
 * perm_to_intll: Safe for n <= 20
 */
#ifndef INT_PERM_H
#define INT_PERM_H

#include <vector>

using namespace std;

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
