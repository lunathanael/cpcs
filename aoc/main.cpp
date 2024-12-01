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

/* START OPTIONAL INCLUDES */
#include "lib/bitmanip.hpp"
#include "lib/io.hpp"
#include "lib/macros.hpp"

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

LL part_one() {
  auto in = read_file("input_1.txt");

  VL v1;
  VL v2;
  LL i;
  while (cin >> i) {
    v1.pb(i);
    in >> i;
    v2.pb(i);
  }

  SORT(v1);
  SORT(v2);

  LL ans = 0;
  FOR(i, 0, v1.size()) { ans += abs(v1[i] - v2[i]); }

  return ans;
}

LL part_two() {
  auto in = read_file("input_2.txt");
  VL v1;
  VL v2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  TEST_ONLY(DMARK; for (int i = 0; i < 64; ++i) {
    LL j = 1LL << i;

    if (!is_pow2(j)) {
      DMARK;
      DVALUE(i);
      DVALUE(j);
    }
  } DMARK;)

  cout << popcount(1023) << endl;

  // Start here

  // cout << part_one() << endl;
  return 0;
}
