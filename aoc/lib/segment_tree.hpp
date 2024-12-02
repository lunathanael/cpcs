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
#include <vector>

using namespace std;

template <typename F, typename T = int> struct SegTree {
  static constexpr T unit = numeric_limits<T>::min();
  static F f;
  vector<T> s;
  int n;
  SegTree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}

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
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 */
// #include "../various/BumpAllocator.h"
const int inf = 1e9;
struct Node {
  Node *l = nullptr, *r = nullptr;
  int lo, hi, mset = inf, madd = 0, val = -inf;
  Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of -inf
  ~Node() {
    delete l;
    delete r;
  }
  Node(vector<int> &v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l = new Node(v, lo, mid);
      r = new Node(v, mid, hi);
      // val = max(l->val, r->val);
      val = l->val + r->val;
    } else
      val = v[lo];
  }
  int query(int L, int R) {
    if (R <= lo || hi <= L)
      return 0;
    if (L <= lo && hi <= R)
      return val;
    push();

    // return max(l->query(L, R), r->query(L, R));
    return l->query(L, R) + r->query(L, R);
  }
  void set(int L, int R, int x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R)
      mset = val = x, madd = 0;
    else {
      push(), l->set(L, R, x), r->set(L, R, x);
      // val = max(l->val, r->val);
      val = l->val + r->val;
    }
  }
  void add(int L, int R, int x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R) {
      if (mset != inf)
        mset += x;
      else
        madd += x;
      val += x;
    } else {
      push(), l->add(L, R, x), r->add(L, R, x);
      // val = max(l->val, r->val);
      val = l->val + r->val;
    }
  }
  void push() {
    if (!l) {
      int mid = lo + (hi - lo) / 2;
      l = new Node(lo, mid);
      r = new Node(mid, hi);
    }
    if (mset != inf)
      l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
    else if (madd)
      l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
  }
};

struct LazySegTree {
  Node *root;
  LazySegTree(vector<int> &v) : root(new Node(v, 0, v.size())) {}
  ~LazySegTree() { delete root; }
  int query(int L, int R) { return root->query(L, R); }
  void set(int L, int R, int x) { root->set(L, R, x); }
  void add(int L, int R, int x) { root->add(L, R, x); }
};

#endif
