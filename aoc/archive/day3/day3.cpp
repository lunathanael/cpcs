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
  STR s;
  while (getline(in, s)) {
    vs.pb(s);
  }
}

void part1() {
  int sum = 0;
  regex pattern(R"(mul\((\d+),(\d+)\))");
  smatch match;
  FORE(s, vs) {
    while (regex_search(s, match, pattern)) {
      int a = stoi(match[1]);
      int b = stoi(match[2]);
      sum += a * b;
      s = match.suffix();
    }
  }
  cout << sum << endl;
}

void part2() {
  int sum = 0;
  bool summing = true;
  regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
  smatch match;
  FORE(s, vs) {
    while (regex_search(s, match, pattern)) {
      string op = match[0];
      // cout << op << endl;
      if (op == "do()") {
        summing = true;
      } else if (op == "don't()") {
        summing = false;
      } else {
        int a = stoi(match[1]);
        int b = stoi(match[2]);
        if (summing) {
          sum += a * b;
        }
      }
      s = match.suffix();
    }
  }
  cout << sum << endl;
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
