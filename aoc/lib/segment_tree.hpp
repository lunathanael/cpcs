/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and
 * exclusive to the right. Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 */
#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <limits>
#include <vector>

using namespace std;

template <typename F, typename T = int> struct Tree {
  static constexpr T unit = numeric_limits<T>::min();
  T f(T a, T b) { return F(a, b); } // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; (pos /= 2) != 0;) {
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
  }
  T query(int b, int e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if ((b % 2) != 0) {
        ra = f(ra, s[b++]);
      }
      if ((e % 2) != 0) {
        rb = f(s[--e], rb);
      }
    }
    return f(ra, rb);
  }
};

#endif
