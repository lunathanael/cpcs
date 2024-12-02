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

#define FHM_RANDOMIZE false

/* START OPTIONAL INCLUDES */
#include "lib/bitmanip.hpp"
#include "lib/combinatorics.hpp"
#include "lib/io.hpp"
#include "lib/macros.hpp"
// #include "lib/segment_tree.hpp"
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

int part1() {
  auto in = read_file("in.txt");
  int safee = 0;
  string s;
  VVI grid;
  while (getline(in, s)) {
    VI v;
    stringstream ss(s);
    int i;
    while (ss >> i) {
      v.pb(i);
    }
    grid.pb(v);
  }

  FORE(row, grid) {
    bool safe = is_sorted(ALL(row)) || is_sorted(ALLR(row));
    if (!safe) {
      continue;
    }

    FOR(i, 1, SZ(row) - 1) {
      if (!LINR(abs(row[i] - row[i - 1]), 1, 3)) {
        safe = false;
        break;
      }
      if (!LINR(abs(row[i] - row[i + 1]), 1, 3)) {
        safe = false;
        break;
      }
    }
    safee += SCAST(int, safe);
  }
  return safee;
}

int part2() {
  auto in = read_file("in.txt");
  int safee = 0;
  string s;
  VVI grid;
  while (getline(in, s)) {
    VI v;
    stringstream ss(s);
    int i;
    while (ss >> i) {
      v.pb(i);
    }
    grid.pb(v);
  }

  FORE(r, grid) {
    auto check = [](auto row) {
      if (!is_sorted(ALL(row)) && !is_sorted(ALLR(row))) {
        return false;
      }

      FOR(i, 1, SZ(row) - 1) {
        if (!LINR(abs(row[i] - row[i - 1]), 1, 3)) {
          return false;
        }
        if (!LINR(abs(row[i] - row[i + 1]), 1, 3)) {
          return false;
        }
      }
      return true;
    };
    bool safe = check(r);
    if (!safe) {
      FOR(i, 0, SZ(r)) {
        VI tmp = r;
        tmp.erase(tmp.begin() + i);
        if (check(tmp)) {
          safe = true;
          break;
        }
      }
    }
    safee += SCAST(int, safe);
  }
  return safee;
}

int main() {
  IOSOPT;
  // Start here
  cout << part1() << endl;
  cout << part2() << endl;
  return 0;
}
