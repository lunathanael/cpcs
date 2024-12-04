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

VS vs;

void process() {
  auto in = read_file("in.txt");
  string s;
  while (in >> s) {
    vs.pb(s);
  }
}

void part1() {
  int n = SZ(vs), m = n ? SZ(vs[0]) : 0;
  if (!n)
    return;

  string target = "XMAS";
  int ans = 0;
  auto check = [&](string s) { ans += (s == target); };

  REP(i, n) REP(j, m - 3) {
    string s1, s2;
    REP(k, 4) {
      s1 += vs[i][j + k];
      s2 = vs[i][j + k] + s2;
    }
    check(s1);
    check(s2);
  }

  REP(i, n - 3) REP(j, m) {
    string s1, s2;
    REP(k, 4) {
      s1 += vs[i + k][j];
      s2 = vs[i + k][j] + s2;
    }
    check(s1);
    check(s2);
  }

  REP(i, n - 3) {
    REP(j, m - 3) {
      string s1, s2;
      REP(k, 4) {
        s1 += vs[i + k][j + k];
        s2 = vs[i + k][j + k] + s2;
      }
      check(s1);
      check(s2);
    }
    FOR(j, 3, m) {
      string s1, s2;
      REP(k, 4) {
        s1 += vs[i + k][j - k];
        s2 = vs[i + k][j - k] + s2;
      }
      check(s1);
      check(s2);
    }
  }

  cout << ans << endl;
}

void part2() {
  int ans = 0;
  string target = "MAS";

  int n = SZ(vs);
  int m = SZ(vs[0]);

  FOR(i, 1, n - 1) {
    FOR(j, 1, m - 1) {
      if (vs[i][j] == 'A') {
        bool tl = (vs[i - 1][j - 1] == 'M' && vs[i + 1][j + 1] == 'S') ||
                  (vs[i - 1][j - 1] == 'S' && vs[i + 1][j + 1] == 'M');
        bool tr = (vs[i - 1][j + 1] == 'M' && vs[i + 1][j - 1] == 'S') ||
                  (vs[i - 1][j + 1] == 'S' && vs[i + 1][j - 1] == 'M');

        if (tl && tr) {
          ans++;
        }
      }
    }
  }

  cout << ans << endl;
}

int main() {
  IOSOPT;
  process();
  part1();
  part2();

  return 0;
}
