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

#include <functional>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

template <typename F, typename T = int, T unit = T{}> struct SegTree {
  static F f;
  vector<T> s;
  int n;
  SegTree(const int n) : s(2 * n, unit), n(n) {}

  template <typename It>
  SegTree(const vector<T> &v) : s(2 * v.size(), unit), n(v.size()) {
    init(begin(v), end(v));
  }

  template <typename It> void init(It first, It last) {
    copy(first, last, begin(s) + n);
    for (int i = n - 1; i > 0; --i) {
      s[i] = f(s[i * 2], s[i * 2 + 1]);
    }
  }

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

/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Segment tree to add or set values of large intervals.
 * Use bump allocator for perf, and SmallPtr or implicit indices for memory.
 * Time: O(log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 */
template <typename F, typename T = int, T unit = T{}> struct _LAZYSEGTREENODE {
  static F f;

  _LAZYSEGTREENODE *l = nullptr, *r = nullptr;
  int lo, hi;
  T mset = unit, madd = T{}, val = unit;

  _LAZYSEGTREENODE(int lo, int hi) : lo(lo), hi(hi) {}
  ~_LAZYSEGTREENODE() {
    delete l;
    delete r;
  }

  _LAZYSEGTREENODE(const vector<T> &v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l = new _LAZYSEGTREENODE(v, lo, mid);
      r = new _LAZYSEGTREENODE(v, mid, hi);
      val = f(l->val, r->val);
    } else
      val = v[lo];
  }

  T query(int L, int R) {
    if (R <= lo || hi <= L)
      return unit;
    if (L <= lo && hi <= R)
      return val;
    push();
    return f(l->query(L, R), r->query(L, R));
  }

  void update(int L, int R, T x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R)
      mset = val = x, madd = T{};
    else {
      push(), l->update(L, R, x), r->update(L, R, x);
      val = f(l->val, r->val);
    }
  }

  void add(int L, int R, T x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R) {
      if (mset != unit)
        mset += x;
      else
        madd += x;
      val += x;
    } else {
      push(), l->add(L, R, x), r->add(L, R, x);
      val = f(l->val, r->val);
    }
  }

  void push() {
    if (!l) {
      int mid = lo + (hi - lo) / 2;
      l = new _LAZYSEGTREENODE(lo, mid);
      r = new _LAZYSEGTREENODE(mid, hi);
    }
    if (mset != unit)
      l->update(lo, hi, mset), r->update(lo, hi, mset), mset = unit;
    else if (madd != T{})
      l->add(lo, hi, madd), r->add(lo, hi, madd), madd = T{};
  }
};

template <typename F, typename T = int, T unit = T{}> struct LazySegTree {
  _LAZYSEGTREENODE<F, T, unit> *root;
  LazySegTree(const int lo, const int hi)
      : root(new _LAZYSEGTREENODE<F, T, unit>(lo, hi)) {}
  LazySegTree(const vector<T> &v)
      : root(new _LAZYSEGTREENODE<F, T, unit>(v, 0, v.size())) {}
  ~LazySegTree() { delete root; }
  T query(int L, int R) { return root->query(L, R); }
  void update(int L, int R, T x) { root->update(L, R, x); }
  void add(int L, int R, T x) { root->add(L, R, x); }
  void push() { root->push(); }
};

struct _MAX {
  constexpr int operator()(const int &x, const int &y) const {
    return max(x, y);
  }
};

struct _MIN {
  constexpr int operator()(const int &x, const int &y) const {
    return min(x, y);
  }
};

struct _GCD {
  constexpr int operator()(const int &x, const int &y) const {
    return gcd(x, y);
  }
};

struct _LCM {
  constexpr int operator()(const int &x, const int &y) const {
    return lcm(x, y);
  }
};

struct _AND {
  constexpr int operator()(const int &x, const int &y) const { return x & y; }
};

struct _OR {
  constexpr int operator()(const int &x, const int &y) const { return x | y; }
};

struct _XOR {
  constexpr int operator()(const int &x, const int &y) const { return x ^ y; }
};

using SegTreeSum = SegTree<plus<>, int, 0>;
using SegTreeMax = SegTree<_MAX, int, numeric_limits<int>::min()>;
using SegTreeMin = SegTree<_MIN, int, numeric_limits<int>::max()>;
using SegTreeGCD = SegTree<_GCD, int, 0>;
using SegTreeLCM = SegTree<_LCM, int, 0>;
using SegTreeAND = SegTree<_AND, int, 0>;
using SegTreeOR = SegTree<_OR, int, 0>;
using SegTreeXOR = SegTree<_XOR, int, 0>;

using LazySegTreeSum = LazySegTree<plus<>, int, 0>;
using LazySegTreeMax = LazySegTree<_MAX, int, numeric_limits<int>::min()>;
using LazySegTreeMin = LazySegTree<_MIN, int, numeric_limits<int>::max()>;
using LazySegTreeGCD = LazySegTree<_GCD, int, 0>;
using LazySegTreeLCM = LazySegTree<_LCM, int, 0>;
using LazySegTreeAND = LazySegTree<_AND, int, 0>;
using LazySegTreeOR = LazySegTree<_OR, int, 0>;
using LazySegTreeXOR = LazySegTree<_XOR, int, 0>;

#endif
