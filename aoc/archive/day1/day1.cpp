// change to O3 to disable fast-math for geometry problems
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

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
#include "lib/fasthashmap.hpp"
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
  auto in = read_file("in.txt");

  VL v1;
  VL v2;
  LL i;
  while (in >> i) {
    v1.pb(i);
    DVALUE(i);
    in >> i;
    DVALUE(i);
    v2.pb(i);
  }

  SORT(v1);
  SORT(v2);

  LL ans = 0;
  FOR(i, 0, v1.size()) { ans += abs(v1[i] - v2[i]); }

  return ans;
}

LL part_two() {
  auto in = read_file("in.txt");
  VL v1;
  VL v2;
  LL i;
  while (in >> i) {
    v1.pb(i);
    in >> i;
    v2.pb(i);
  }

  UMP<LL, LL> mp;
  FORE(ele, v2) { mp[ele]++; }

  LL ans = 0;
  FORE(ele, v1) { ans += ele * mp[ele]; }

  return ans;
}

int main() {
  IOSOPT;

  // Start here

  cout << part_one() << endl;
  cout << part_two() << endl;
  return 0;
}
