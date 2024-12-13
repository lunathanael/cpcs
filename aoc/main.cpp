#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native,popcnt")

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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define FHM_RANDOMIZE false

/* START OPTIONAL INCLUDES */
#include "lib/aoc.hpp"
#include "lib/bitmanip.hpp"
#include "lib/combinatorics.hpp"
#include "lib/fasthashmap.hpp"
#include "lib/io.hpp"
#include "lib/macros.hpp"
#include "lib/matrix.hpp"
#include "lib/numbers.hpp"
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

int main() {
  IOSOPT;
  // Start here
  Matrix<int, 3, 3> m;
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;
  m[2][0] = 7;
  m[2][1] = 8;
  m[2][2] = 9;
  print(m);
  print(m * m);
  Vector<int, 3> v(10);
  print(v);
  print(m * v);

  Matrix<LL, 3, 3> m2(m);
  print(m2 ^ 10);
  LL vv = 0;

  return 0;
}
