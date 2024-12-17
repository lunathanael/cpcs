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

Point<int> start;

void process() {
  REP(i, vs.size()) {
    REP(j, vs[i].size()) {
      if (vs[i][j] == 'S') {
        start = {i, j};
        break;
      }
    }
  }
}

struct PHASH {
  size_t operator()(const Point<int> &p) const { return p.x * 1000000 + p.y; }
};

struct PHASH2 {
  size_t operator()(const pair<Point<int>, int> &p) const { return p.first.x * 1000000 + p.first.y * 1000 + p.second; }
};

ULL ans = 0;
Point<int> epos;

void part1() {
  UST<pair<Point<int>, int>, PHASH2> vis;
  PQI<tuple<ULL, Point<int>, int>> q;
  q.emplace(0, start, 1);
  while (!q.empty()) {
    Point<int> cur = get<1>(q.top());
    int dir = get<2>(q.top());
    ULL dist = get<0>(q.top());
    q.pop();
    if (vs[cur.x][cur.y] == '#')
      continue;
    if (HAS(vis, mp(cur, dir)))
      continue;
    vis.insert(mp(cur, dir));
    if (vs[cur.x][cur.y] == 'E') {
      ans = dist;
      epos = cur;
      break;
    }
    Point<int> nxt = cur + DIRXY[dir];
    q.emplace(dist + 1, nxt, dir);
    REP(i, 4) {
      q.emplace(dist + 1000, cur, (dir + 1) % 4);
      q.emplace(dist + 1000, cur, (dir + 3) % 4);
    }
  }
  print(ans);
}

void part2() {
  UST<Point<int>, PHASH> has;

  UMP<pair<Point<int>, int>, ULL, PHASH2> vis;
  PQI<tuple<ULL, Point<int>, int, vector<Point<int>>>> q;
  q.emplace(0, start, 1, vector<Point<int>>());
  while (!q.empty()) {
    Point<int> cur = get<1>(q.top());
    int dir = get<2>(q.top());
    ULL dist = get<0>(q.top());
    vector<Point<int>> path = get<3>(q.top());
    path.push_back(cur);
    q.pop();
    if (vs[cur.x][cur.y] == '#')
      continue;
    if (HAS(vis, mp(cur, dir)) && vis[mp(cur, dir)] < dist)
      continue;
    vis[mp(cur, dir)] = dist;
    if (vs[cur.x][cur.y] == 'E' && dist == ans) {
      ans = dist;
      EACH(p, path) {
        has.insert(p);
      }
    }
    Point<int> nxt = cur + DIRXY[dir];
    q.emplace(dist + 1, nxt, dir, path);
    q.emplace(dist + 1001, cur + DIRXY[(dir + 1) % 4], (dir + 1) % 4, path);
    q.emplace(dist + 1001, cur + DIRXY[(dir + 3) % 4], (dir + 3) % 4, path);
  }
  print(has.size());
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();
  return 0;
}
