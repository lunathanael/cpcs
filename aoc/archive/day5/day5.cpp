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

UMP<int, VI> ump;
VVI vvi;

void process() {
  int i = 0;
  while (!vs[i].empty()) {
    auto pos = vs[i].find('|');
    int j = stoi(vs[i].substr(0, pos));
    int k = stoi(vs[i].substr(pos + 1));
    ump[k].pb(j);
    i++;
  }
  FOR(idx, i + 1, vs.size()) {
    stringstream ss(vs[idx]);
    string num;
    VI row;
    while (getline(ss, num, ',')) {
      row.pb(stoi(num));
    }
    vvi.pb(row);
  }
}

void part1() {
  LL ans = 0;
  FORE(const &v, vvi) {
    UST<int> pres(ALL(v));
    UST<int> ust;
    bool valid = true;
    FORE(const &i, v) {
      if (HAS(ump, i)) {
        FORE(const &j, ump[i]) {
          if (!HAS(ust, j) && HAS(pres, j)) {
            valid = false;
            break;
          }
        }
      }
      ust.insert(i);
    }
    if (valid) {
      ans += v[v.size() / 2];
    }
  }
  cout << ans << endl;
}

void part2() {
  LL ans = 0;
  FORE(&v, vvi) {
    UST<int> pres(ALL(v));
    UST<int> ust;
    bool valid = false;
    FORE(const &i, v) {
      if (HAS(ump, i)) {
        FORE(const &j, ump[i]) {
          if (!HAS(ust, j) && HAS(pres, j)) {
            sort(ALL(v), [&](int a, int b) { return AHAS(ump[b], a); });
            valid = true;
          }
        }
      }
      ust.insert(i);
    }
    if (valid) {
      ans += v[v.size() / 2];
    }
  }
  cout << ans << endl;
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();
  return 0;
}
