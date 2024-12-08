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
UMP<char, VII> ump;

void process() {
  REP(i, SZ(vs)) {
    REP(j, SZ(vs[i])) {
      if (vs[i][j] != '.') {
        ump[vs[i][j]].eb(i, j);
      }
    }
  }
}

void part1() {
  UST<PII, hash_pair> ust;
  EACH(&pi, ump) {
    auto &pairs = pi.se;
    EACH(p1, pairs) {
      EACH(p2, pairs) {
        if (p1 == p2) {
          continue;
        }
        int dx = p2.fi - p1.fi;
        int dy = p2.se - p1.se;
        ust.insert(mp(p1.fi - dx, p1.se - dy));
        ust.insert(mp(p2.fi + dx, p2.se + dy));
      }
    }
  }
  LL ans = 0;
  EACH(p, ust) {
    if (LINR(p.fi, 0, SZ(vs) - 1) && LINR(p.se, 0, SZ(vs[0]) - 1)) {
      ans++;
    }
  }
  print(ans);
}

void part2() {
  UST<PII, hash_pair> ust;
  EACH(&pi, ump) {
    auto pairs = pi.se;
    EACH(p1, pairs) {
      EACH(p2, pairs) {
        if (p1 == p2) {
          continue;
        }
        int dx = p2.fi - p1.fi;
        int dy = p2.se - p1.se;

        auto left = p1;
        while (LINR(left.fi, 0, SZ(vs) - 1) &&
               LINR(left.se, 0, SZ(vs[0]) - 1)) {
          ust.insert(left);
          left.fi -= dx;
          left.se -= dy;
        }

        auto right = p2;
        while (LINR(right.fi, 0, SZ(vs) - 1) &&
               LINR(right.se, 0, SZ(vs[0]) - 1)) {
          ust.insert(right);
          right.fi += dx;
          right.se += dy;
        }
      }
    }
  }
  LL ans = 0;
  EACH(p, ust) {
    if (LINR(p.fi, 0, SZ(vs) - 1) && LINR(p.se, 0, SZ(vs[0]) - 1)) {
      ans++;
    }
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
