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
const int rows = SZ(vs);
const int cols = SZ(vs[0]);

LL ans1{0}, ans2{0};

LL encode(U32 x, U32 y) { return (static_cast<LL>(x) << 32) | static_cast<LL>(y); }

void process() {
  VVI visited(rows, VI(cols, 0));

  auto flood_fill = [&](int start_i, int start_j) {
    const char target = vs[start_i][start_j];

    LL area = 0;
    LL wall_count = 0;

    vector<UST<LL>> boundaries(4);
  
    queue<PII> q;
    if (visited[start_i][start_j])
      return;
    q.emplace(start_i, start_j);
    visited[start_i][start_j] = 1;

    while (SZ(q)) {
      auto [x, y] = q.front();
      q.pop();
      area++;

      REP(k, 4) {
        int nx = x + DIRXY[k][0];
        int ny = y + DIRXY[k][1];

        if ((!LIN(nx, 0, rows)) || (!LIN(ny, 0, cols)) ||
            vs[nx][ny] != target) {
          boundaries[k].insert(encode(nx, ny));
          wall_count++;
        } else if (!visited[nx][ny]) {
          visited[nx][ny] = 1;
          q.emplace(nx, ny);
        }
      }
    }

    LL distinct_perimeter = 0;
    bool is_edge = false;
    REP(k, 2) {
      FOR(x, -1, rows + 1) {
        FOR(y, -1, cols + 1) {
          if (HAS(boundaries[k*2], encode(x, y)))
            is_edge = true;
          else if (is_edge) {
            distinct_perimeter++;
            is_edge = false;
          }
        }
        distinct_perimeter += is_edge;
        is_edge = false;
      }
      FOR(y, -1, cols + 1) {
        FOR(x, -1, rows + 1) {
          if (HAS(boundaries[k*2+1], encode(x, y)))
            is_edge = true;
          else if (is_edge) {
            distinct_perimeter++;
            is_edge = false;
          }
        }
        distinct_perimeter += is_edge;
        is_edge = false;
      }
    }
    ans1 += area * wall_count;
    ans2 += area * distinct_perimeter;
  };

  REP(i, rows) {
    REP(j, cols) {
      flood_fill(i, j);
    }
  }
}

void part1() { print(ans1); }

void part2() { print(ans2); }

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
