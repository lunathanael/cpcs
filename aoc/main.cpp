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

// Create a segment tree that performs addition
BINOP(add, a + b);

int main() {
  IOSOPT;

  // LazySegTree<add<int>, int> seg(10, 0); // Size 10, initialized with 0
  // Test basic operations
  vector<int> v = {0, 0, 5, 0, 3, 0, 0, 2};
  LazySegTree seg(v);

  // Test range queries
  cout << "Sum [0,4]: " << seg.query(0, 4 + 1) << "\n"; // Should be 8 (5 + 3)
  cout << "Sum [2,7]: " << seg.query(2, 7 + 1)
       << "\n"; // Should be 10 (5 + 3 + 2)
  cout << "Sum [0,9]: " << seg.query(0, 9 + 1)
       << "\n"; // Should be 10 (total sum)

  // Test single point update and query
  seg.set(2, 2, 1); // Change position 2 from 5 to 1
  cout << "After update, Sum [0,4]: " << seg.query(0, 4)
       << "\n"; // Should be 4 (1 + 3)

  return 0;
}
