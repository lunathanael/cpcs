#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("popcnt")

#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define FHM_RANDOMIZE false

/* START OPTIONAL INCLUDES */
#include "lib/bitmanip.hpp"
#include "lib/combinatorics.hpp"
#include "lib/io.hpp"
#include "lib/macros.hpp"
#include "lib/segment_tree.hpp"
/* END OPTIONAL INCLUDES */

using namespace std;

struct hash_pair {
  template <class T1, class T2> size_t operator()(const pair<T1, T2> &p) const {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);
    if (hash1 != hash2) {
      return hash1 ^ hash2;
    }
    return hash1;
  }
};

BINOP(MAX, max(x, y));

void test_regular_segtree() {
  cout << "\n=== Testing Regular SegTree ===\n";
  vector<int> arr = {1, 3, 5, 7, 9, 11};

  // Test sum segment tree
  SegTree<plus<int>> sum_st(arr.size());
  sum_st.init(arr.begin(), arr.end());

  cout << "Sum [0,3): " << sum_st.query(0, 3) << " (should be 9)\n";
  sum_st.update(1, 4); // Change 3 to 4
  cout << "Sum [0,3) after update: " << sum_st.query(0, 3)
       << " (should be 10)\n";

  // Test max segment tree
  SegTree<MAX<int>> max_st(arr.size());
  max_st.init(arr.begin(), arr.end());

  cout << "Max [0,3): " << max_st.query(0, 3) << " (should be 5)\n";
  max_st.update(1, 8); // Change 3 to 8
  cout << "Max [0,3) after update: " << max_st.query(0, 3)
       << " (should be 8)\n";
}

void test_lazy_segtree() {
  cout << "\n=== Testing Lazy SegTree ===\n";
  vector<int> arr = {1, 3, 5, 7, 9, 11};

  // Test sum lazy segment tree
  LazySegTree<plus<>> sum_lst(arr);
  cout << "Sum [0,3): " << sum_lst.query(0, 3) << " (should be 9)\n";
  sum_lst.add(0, 3, 2); // Add 2 to range [0,3)
  cout << "Sum [0,3) after adding 2: " << sum_lst.query(0, 3)
       << " (should be 15)\n";
  sum_lst.update(1, 3, 4); // Set range [1,3) to 4
  cout << "Sum [0,3) after setting [1,3) to 4: " << sum_lst.query(0, 3)
       << " (should be 9)\n";

  // Test max lazy segment tree
  LazySegTreeMax max_lst(arr);
  cout << "Max [0,3): " << max_lst.query(0, 3) << " (should be 5)\n";
  max_lst.add(0, 3, 2); // Add 2 to range [0,3)
  cout << "Max [0,3) after adding 2: " << max_lst.query(0, 3)
       << " (should be 7)\n";
  max_lst.update(1, 3, 10); // Set range [1,3) to 10
  cout << "Max [0,3) after setting [1,3) to 10: " << max_lst.query(0, 3)
       << " (should be 10)\n";
}

int main() {
  test_regular_segtree();
  test_lazy_segtree();
  return 0;
}
