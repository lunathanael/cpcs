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

int n, m;
VS grid, g2;
STR instr;
LL ans1{0}, ans2{0};
Point<int> pos;

void process() {

  STR line;
  int i = 0;
  while (!vs[i].empty()) {
    grid.pb(vs[i]);
    i++;
  }
  i++;
  while (i < SZ(vs)) {
    instr += vs[i];
    i++;
  }

  REP(i, SZ(grid)) {
    REP(j, SZ(grid[i])) {
      if (grid[i][j] == '@') {
        pos = Point(j, i);
        break;
      }
    }
  }

  n = SZ(grid), m = SZ(grid[0]);
  g2 = grid;
}

ULL box_coords() {
  ULL ret = 0;
  REP(i, n) {
    REP(j, m) {
      if (grid[i][j] == 'O' || grid[i][j] == '[') {
        ret += (100ULL * i + j);
      }
    }
  }
  return ret;
}

bool check_box(Point<int> pos, int dir) {
  if (grid[pos.y][pos.x] == '#')
    return true;
  if (grid[pos.y][pos.x] == 'O') {
    Point<int> new_pos = pos + DIRXY[dir];
    if (check_box(new_pos, dir)) {
      return true;
    } else {
      grid[new_pos.y][new_pos.x] = 'O';
      return false;
    }
  }
  return false;
}

bool check_box2(Point<int> pos, int dir) {
  if (grid[pos.y][pos.x] == '#')
    return true;
  if (grid[pos.y][pos.x] == '[' || grid[pos.y][pos.x] == ']') {
    Point<int> new_pos = pos + DIRXY[dir];
    if (check_box2(new_pos, dir)) {
      return true;
    } else {
      grid[new_pos.y][new_pos.x] = grid[pos.y][pos.x];
      return false;
    }
  }
  return false;
}

struct PHASH {
  size_t operator()(const Point<int> &p) const {
    return p.x * 1000000 + p.y;
  }
};

bool move_boxes_vertical(Point<int> pos, int dir) {
  queue<Point<int>> q;
  q.push(pos);
  UMP<Point<int>, char, PHASH> visited;

  while (!q.empty()) {
    Point<int> cur = q.front();
    q.pop();
    if (grid[cur.y][cur.x] == '#')
      return true;

    if (grid[cur.y][cur.x] == '.')
      continue;
    visited[cur] = grid[cur.y][cur.x];

    Point<int> new_pos = cur + DIRXY[dir];
    q.push(new_pos);

    if (grid[new_pos.y][new_pos.x] == '[') {
      q.push(new_pos + Point<int>{1, 0});
    } else if (grid[new_pos.y][new_pos.x] == ']') {
      q.push(new_pos + Point<int>{-1, 0});
    }
  }
  EACH(p, visited) {
    grid[p.first.y][p.first.x] = '.';
  }
  EACH(p, visited) {
    Point<int> new_pos = p.first + DIRXY[dir];
    grid[new_pos.y][new_pos.x] = p.second;
  }
  return false;
}

void part1() {

  EACH(c, instr) {
    int dir = -1;
    switch (c) {
    case '>':
      dir = 0;
      break;
    case 'v':
      dir = 1;
      break;
    case '<':
      dir = 2;
      break;
    case '^':
      dir = 3;
      break;
    default:
      assert(false);
    }
    Point new_pos = pos + DIRXY[dir];
    if (!LINR(new_pos.x, 0, m - 1) || !LINR(new_pos.y, 0, n - 1))
      continue;
    if (grid[new_pos.y][new_pos.x] == '#')
      continue;
    if (grid[new_pos.y][new_pos.x] == 'O') {
      if (check_box(new_pos, dir)) {
        continue;
      }
    }
    grid[pos.y][pos.x] = '.';
    pos = new_pos;
    grid[pos.y][pos.x] = '@';
  }

  print("Part 1: ", box_coords());
}

void part2() {
  VS new_grid;
  REP(i, n) {
    string line;
    REP(j, m) {
      switch (g2[i][j]) {
      case '@':
        line += "@.";
        break;
      case 'O':
        line += "[]";
        break;
      case '.':
        line += "..";
        break;
      case '#':
        line += "##";
        break;
      }
    }
    new_grid.pb(line);
  }

  grid = new_grid;
  n = SZ(grid), m = SZ(grid[0]);

  REP(i, n) {
    REP(j, m) {
      if (grid[i][j] == '@') {
        pos = Point(j, i);
        break;
      }
    }
  }

  EACH(c, instr) {
    // EACH(line, grid) { print(line); }
    int dir = -1;
    switch (c) {
    case '>':
      dir = 0;
      break;
    case 'v':
      dir = 1;
      break;
    case '<':
      dir = 2;
      break;
    case '^':
      dir = 3;
      break;
    default:
      assert(false);
    }
    Point new_pos = pos + DIRXY[dir];
    if (grid[new_pos.y][new_pos.x] == '#')
      continue;
    if (grid[new_pos.y][new_pos.x] != '.') {
      if (DIRXY[dir][1] == 0) {
        if (check_box2(new_pos, dir)) {
          continue;
        }
      } else {
        if (move_boxes_vertical(pos, dir)) {
          continue;
        }
      }
    }
    grid[pos.y][pos.x] = '.';
    pos = new_pos;
    grid[pos.y][pos.x] = '@';
    // grid[pos.y][pos.x] = '.';
    // pos = new_pos;
    // if (grid[pos.y][pos.x - 1] == '[') {
    //   grid[pos.y][pos.x - 1] = '.';
    // } else if (grid[pos.y][pos.x + 1] == ']') {
    //   grid[pos.y][pos.x + 1] = '.';
    // }
    // grid[pos.y][pos.x] = '@';
  }
  // print(grid);
  ans2 = box_coords();
  print("Part 2: ", ans2);
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
