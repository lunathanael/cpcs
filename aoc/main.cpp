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
#include "lib/aoc.hpp"
#include "lib/bitmanip.hpp"
#include "lib/combinatorics.hpp"
#include "lib/io.hpp"
#include "lib/macros.hpp"
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

VVL vvl;
void process() {
  // process 190: 10 19 into vector of vector of {190, 10, 19}
  VS vs = read_aoc("in.txt");
  EACH(const &s, vs) {
    stringstream ss(s);
    string tmp;
    VL nums;
    while (getline(ss, tmp, ':')) {
      stringstream ss2(tmp);
      LL num;
      while (ss2 >> num) {
        nums.pb(num);
      }
    }
    vvl.pb(nums);
  }
}

template <bool concat = false>
bool dfs(const VL &row, long long curr, int idx = 1) {
  if (idx == SZ(row) - 1) {
    return curr == row[0];
  }
  if (curr >= row[0])
    return false;
  if constexpr (concat) {
    if (dfs<true>(row, stoll(to_string(curr) + to_string(row[idx + 1])),
                  idx + 1)) {
      return true;
    }
  }
  if (dfs<concat>(row, curr * row[idx + 1], idx + 1)) {
    return true;
  }
  if (dfs<concat>(row, curr + row[idx + 1], idx + 1)) {
    return true;
  }
  return false;
};

void part1() {
  long long ans = accumulate(ALL(vvl), 0LL, [&](LL curr, const VL &row) {
    if (dfs(row, row[1])) {
      return curr + row[0];
    }
    return curr;
  });
  print(ans);
}

void part2() {
  long long ans = accumulate(ALL(vvl), 0LL, [&](LL curr, const VL &row) {
    if (dfs<true>(row, row[1])) {
      return curr + row[0];
    }
    return curr;
  });
  print(ans);
}

int main() {
  IOSOPT;
  // Start here
  // process();
  fast_process();
  part1();
  part2();

  return 0;
}
