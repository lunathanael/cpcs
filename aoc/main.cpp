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
int posx, posy;
void process() {

  REP(i, SZ(vs)) {
    REP(j, SZ(vs[i])) {
      if (vs[i][j] == '>' || vs[i][j] == '<' || vs[i][j] == '^' ||
          vs[i][j] == 'v') {
        posx = j;
        posy = i;
        break;
      }
    }
  }
  static_cast<void>(vs);
  return;
}

void part1() {
  LL ans = 0;
  set<PLL> visited;

  int dir = 0;
  if (vs[posy][posx] == 'v')
    dir = 0;
  else if (vs[posy][posx] == '^')
    dir = 1;
  else if (vs[posy][posx] == '>')
    dir = 2;
  else if (vs[posy][posx] == '<')
    dir = 3;
  visited.insert({posx, posy});
  while (true) {
    int newposx = posx + DIRXY[dir][0];
    int newposy = posy + DIRXY[dir][1];
    if (!LINR(newposx, 0, SZ(vs[0]) - 1) || !LINR(newposy, 0, SZ(vs) - 1))
      break;
    if (vs[newposy][newposx] == '#') {
      if (dir == 1)
        dir = 2;
      else if (dir == 3)
        dir = 1;
      else if (dir == 0)
        dir = 3;
      else if (dir == 2)
        dir = 0;
      continue;
    }
    posx = newposx;
    posy = newposy;
    visited.insert({posx, posy});
  }

  print(SZ(visited));
  static_cast<void>(ans);
  return;
}

bool help() {
  LL ans = 0;
  set<tuple<LL, LL, int>> visited;
  int posx, posy;
  REP(i, SZ(vs)) {
    REP(j, SZ(vs[i])) {
      if (vs[i][j] == '>' || vs[i][j] == '<' || vs[i][j] == '^' ||
          vs[i][j] == 'v') {
        posx = j;
        posy = i;
        break;
      }
    }
  }

  int dir = 0;
  if (vs[posy][posx] == 'v')
    dir = 0;
  else if (vs[posy][posx] == '^')
    dir = 1;
  else if (vs[posy][posx] == '>')
    dir = 2;
  else if (vs[posy][posx] == '<')
    dir = 3;
  visited.insert({posx, posy, dir});
  while (true) {
    int newposx = posx + DIRXY[dir][0];
    int newposy = posy + DIRXY[dir][1];
    if (!LINR(newposx, 0, SZ(vs[0]) - 1) || !LINR(newposy, 0, SZ(vs) - 1))
      break;
    if (vs[newposy][newposx] == '#') {
      if (dir == 1)
        dir = 2;
      else if (dir == 3)
        dir = 1;
      else if (dir == 0)
        dir = 3;
      else if (dir == 2)
        dir = 0;
      continue;
    }
    posx = newposx;
    posy = newposy;
    if (visited.find({posx, posy, dir}) != visited.end())
      return false;
    visited.insert({posx, posy, dir});
  }
  return true;
}

void part2() {
  LL ans = 0;
  int posx, posy;
  REP(i, SZ(vs)) {
    REP(j, SZ(vs[i])) {
      if (vs[i][j] == '>' || vs[i][j] == '<' || vs[i][j] == '^' ||
          vs[i][j] == 'v') {
        posx = j;
        posy = i;
        break;
      }
    }
  }

  REP(i, SZ(vs)) {
    REP(j, SZ(vs[i])) {
      if (vs[i][j] != '.')
        continue;
      vs[i][j] = '#';
      ans += !help();
      vs[i][j] = '.';
    }
  }
  cout << ans << endl;
  static_cast<void>(ans);
  return;
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
