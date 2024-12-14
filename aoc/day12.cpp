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
#include "lib/index_hacks.hpp"
#include "lib/io.hpp"
#include "lib/macros.hpp"
#include "lib/matrix.hpp"
#include "lib/numbers.hpp"
#include "lib/point.hpp"
#include "lib/segment_tree.hpp"
#include "lib/system_equations.hpp"
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

    auto parse_coords = [](const string &s) {
      size_t x_pos = s.find('X');
      size_t y_pos = s.find('Y');

      size_t x_start = s.find_first_of("+=", x_pos) + 1;
      size_t x_end = s.find(',', x_start);
      size_t y_start = s.find_first_of("+=", y_pos) + 1;
      size_t y_end = s.length();

      return PLL{stoll(s.substr(x_start, x_end - x_start)),
                 stoll(s.substr(y_start, y_end - y_start))};
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
    PLL buttonB = tup[1_];
    PLL prize = tup[2_];

    Vector buttonA_vec = {buttonA[0_], buttonA[1_]};
    Vector buttonB_vec = {buttonB[0_], buttonB[1_]};
    Vector prize_vec = {prize[0_], prize[1_]};

    Matrix<LL, 2, 2> m;
    m[0][0] = buttonA_vec[0];
    m[0][1] = buttonB_vec[0];
    m[1][0] = buttonA_vec[1];
    m[1][1] = buttonB_vec[1];

    Vector b = {prize_vec[0], prize_vec[1]};

    auto res = solve_linear(m, b);
    if (res[1_] == 2 && all_of(ALL(res[0_]), is_int<double>)) {
      ans1 += round(res[0_][0]) * 3 + round(res[0_][1]);
    }
  }

  print(ans1);
}

Pair<ULL, bool> solve(const Point<LL>& a, const Point<LL>& b, const Point<ULL>& p) {
    const auto [ adiv, amod ] = lldiv(p.y * b.x - p.x * b.y, a.y * b.x - a.x * b.y);
    if(amod != 0) return {0, false};
    const auto [ bdiv, bmod ] = lldiv(p.x - adiv * a.x, b.x);
    if(bmod != 0) return {0, false};
    
    return {adiv * 3 + bdiv, true};
}

void part2() {
  ULL ans2 = 0;

  EACH(&tup, vt) {

    auto add = 10000000000000ULL;
    Vector<LL, 2> buttonA{tup[0_][0_], tup[0_][1_]};
    Vector<LL, 2> buttonB{tup[1_][0_], tup[1_][1_]};
    Vector<ULL, 2> prize{tup[2_][0_] + add, tup[2_][1_] + add};

    auto ans = solve(buttonA, buttonB, prize);
    if (ans[1_]) {
      ans2 += ans[0_];
    }
  }
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
