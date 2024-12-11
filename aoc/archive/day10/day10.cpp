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
#include "lib/fasthashmap.hpp"
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

VS vs = read_aoc("in.txt");

void process() {
  // EACH(&s, vs) {

  // }
}

 LL ans2 = 0;
void dfs(int height, int score, UST<PII, hash_pair> &ust, int x, int y) {
  if (!LIN(x, 0, SZ(vs[0])) || !LIN(y, 0, SZ(vs)))
    return;
  if (vs[y][x] != ('0' + height))
    return;
  // if(HAS(ust, mp(x, y)))
  //   return;
  if (height == 9) {
    ++ans2;
    ust.insert({x, y});
    return;
  }
  // ust.insert({x, y});
  dfs(height + 1, score, ust, x + 1, y);
  dfs(height + 1, score, ust, x - 1, y);
  dfs(height + 1, score, ust, x, y + 1);
  dfs(height + 1, score, ust, x, y - 1);
  // ust.erase({x, y});
}

void part1() {
  LL ans1 = 0;
  REP(i, SZ(vs)) {
    REP(j, SZ(vs[i])) {
      UST<PII, hash_pair> ust;
      dfs(0, 0, ust, j, i);
      ans1 += ust.size();
    }
  }
  print(ans1);
}

void part2() {
  print(ans2);
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
