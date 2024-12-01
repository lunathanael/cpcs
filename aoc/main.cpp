#pragma GCC optimize("O3,unroll-loops")

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
#include <vector>

/* START OPTIONAL INCLUDES */
#include "lib/macros.hpp"
#include "lib/utils/io.h"
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
  VL v1;
  VL v2;
  LL i;
  while (cin >> i) {
    v1.pb(i);
    cin >> i;
    v2.pb(i);
  }

  SORT(v1);
  SORT(v2);

  LL ans = 0;
  FOR(i, 0, v1.size()) { ans += abs(v1[i] - v2[i]); }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // Start here

  cout << part_one() << endl;
  return 0;
}
