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
VI vi;
VII vii;

void process() {
  auto v = vs[0];
  FOR(i, 0, SZ(v)) {
    int id = i / 2;
    int cnt = v[i] - '0';
    int spaces = v[++i] - '0';
    REP(j, cnt) {
      vi.pb(id);
    }
    vii.eb(id, cnt);
    REP(j, spaces) {
      vi.pb(-1);
    }
    vii.eb(-1, spaces);
  }
}

void part1() {
  int l = 0, r = SZ(vi) - 1;
  while (l < r) {
    while (l < r && vi[l] != -1) {
      l++;
    }
    while (l < r && vi[r] == -1) {
      r--;
    }
    if (l < r) {
      swap(vi[l], vi[r]);
      l++;
      r--;
    }
  }
  
  LL ans = 0;
  REP(i, SZ(vi)) {
    if (i > 0 && vi[i] != -1) {
      ans += (vi[i] * i);
    }
  }
  print(ans);
}



void part2() {
  int r = SZ(vii) - 1;
  while (r > 0) {
    while (r > 0 && vii[r].fi == -1) {
      r--;
    }
    
    if (r == 0) break;
    
    int id = vii[r].fi;
    int len = vii[r].se;
    
    int bestPos = -1;
    REP(i, r) {
      if (vii[i].fi == -1 && vii[i].se >= len) {
        bestPos = i;
        break;
      }
    }

    if (bestPos != -1) {
    
      vii[r].fi = -1;
      
      if (vii[bestPos].se > len) {
        vii.insert(vii.begin() + bestPos + 1, {-1, vii[bestPos].se - len});
      }
      
      vii[bestPos] = {id, len};
    }
    --r;
  }
  
  LL ans = 0;
  int idx = 0;
  REP(i, SZ(vii)) {
    if (vii[i].fi != -1) {
      REP(j, vii[i].se) {
        // print(vii[i].fi, idx + j);
        ans += vii[i].fi * (idx + j);
      }
    }
    idx += vii[i].se;
  }
  print(ans);
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
