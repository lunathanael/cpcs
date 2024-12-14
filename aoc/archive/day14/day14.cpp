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

LL ans1{0}, ans2{0};

vector<Pair<Vector<LL, 2>, Vector<LL, 2>>> robots;

void process() {

  for(const auto& s : vs) {
    istringstream iss(s);
    string pos_str, vel_str;
    iss >> pos_str >> vel_str;

    // Parse position
    pos_str = pos_str.substr(2); // Skip "p="
    size_t comma = pos_str.find(',');
    LL px = stoll(pos_str.substr(0, comma));
    LL py = stoll(pos_str.substr(comma + 1));

    // Parse velocity
    vel_str = vel_str.substr(2); // Skip "v="
    comma = vel_str.find(',');
    LL vx = stoll(vel_str.substr(0, comma));
    LL vy = stoll(vel_str.substr(comma + 1));

    robots.pb({{px, py}, {vx, vy}});
  }
}

const LL wide=101;
const LL tall=103;
LL safety() {
  LL q1 = 0, q2 = 0, q3 = 0, q4 = 0;

  int x_mid = wide / 2;
  int y_mid = tall / 2;
  
  EACH(robot, robots) {
    auto pos = robot[0_];
    LL x = pos[0];
    LL y = pos[1];
    
    if (x > x_mid && y > y_mid) q1++;
    else if (x < x_mid && y > y_mid) q2++; 
    else if (x < x_mid && y < y_mid) q3++;
    else if (x > x_mid && y < y_mid) q4++;
  }
  
  return q1 * q2 * q3 * q4;
}

void move(int n) {
  EACH(robot, robots) {
    auto &pos = robot[0_];
    auto &vel = robot[1_];
    pos = pos + vel * n;
    pos[0] = (pos[0] % wide + wide) % wide;
    pos[1] = (pos[1] % tall + tall) % tall;
  }
}

void print_robots() {
  VVI grid(tall, VI(wide, 0));
  EACH(robot, robots) {
    grid[robot[0_][1]][robot[0_][0]] = 1;
  }
  EACH(row, grid) {
    EACH(cell, row) {
      cout << cell;
    }
    cout << endl;
  }
}

bool check_unique() {
  VVI grid(tall, VI(wide, 0));
  for(const auto& robot : robots) {
    if(grid[robot[0_][1]][robot[0_][0]] == 1) {
      return false; 
    }
    grid[robot[0_][1]][robot[0_][0]] = 1;
  }
  return true;
}

void part1() {
  LL ans1 = 0;
  // REP(i, 100) {
  //   move();
  // }
  move(100);
    ans1 = safety();
  print(ans1);
}

void part2() {
  robots.clear();
  process();
  LL ans2 = 0;
  REP(i, 100000) {
    if(check_unique()) {
      print("Unique at", i);
      print_robots();
      break;
    }
    move(1);
  }
  print(ans2);
}

int main() {
  IOSOPT;
  process();
  part1();
  part2();
  // Start here

  return 0;
}
