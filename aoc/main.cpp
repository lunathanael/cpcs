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
#include "lib/system_equations.hpp"
#include "lib/index_hacks.hpp"
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
VT<PLL, PLL, PLL> vt;

void process() {
  REP(i, (SZ(vs) + 1) / 4) {
    string a = vs[i * 4];
    string b = vs[i * 4 + 1];
    string p = vs[i * 4 + 2];
    
    auto parse_coords = [](const string& s) {
      size_t x_pos = s.find('X');
      size_t y_pos = s.find('Y');
      
      size_t x_start = s.find_first_of("+=", x_pos) + 1;
      size_t x_end = s.find(',', x_start);
      size_t y_start = s.find_first_of("+=", y_pos) + 1;
      size_t y_end = s.length();
      
      return PLL{
        stoll(s.substr(x_start, x_end - x_start)),
        stoll(s.substr(y_start, y_end - y_start))
      };
    };
    
    PLL buttonA = parse_coords(a);
    PLL buttonB = parse_coords(b);
    PLL prize = parse_coords(p);
    
    vt.eb(buttonA, buttonB, prize);
  }
}

void part1() {
  LL ans1 = 0;

  EACH(&tup, vt) {
    PLL buttonA = tup[0_];

    Vector buttonA_vec = {buttonA[0_], buttonA[0_]};
    print(buttonA_vec);
  }

}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();

  Matrix m = {{0, 1, 1},{2, 3, 4}};
  print(m);

  return 0;
}
