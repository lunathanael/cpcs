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


ULL ans = 0;
Point<int> epos;

void part1() {
  set<pair<Point<int>, int>> vis;
  priority_queue<tuple<ULL, Point<int>, int>, vector<tuple<ULL, Point<int>, int>>, greater<>> q;
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

void part2(){}

// // int bfs(Point<int> cur, int dir) {
// //   if (vs[cur.x][cur.y] == '#' || vs[cur.x][cur.y] == 'O')
// //     return MOD1e9_7;
// //   if (vs[cur.x][cur.y] == 'E')
// //     return 0;
// //   int found = MOD1e9_7;
// //   char ch = vs[cur.x][cur.y];
// //   vs[cur.x][cur.y] = 'O';
// //   found = min(found, 1 + bfs(cur + DIRXY[dir], dir));
// //   found = min(found, 1001 + bfs(cur + DIRXY[(dir + 1) % 4], (dir + 1) % 4));
// //   found = min(found, 1001 + bfs(cur + DIRXY[(dir + 3) % 4], (dir + 3) % 4));

// //   vs[cur.x][cur.y] = ch;
// //   return found;
// // }

// // bool dfs(Point<int> cur, int dir, int dist) {
// //   if (vs[cur.x][cur.y] == '#' || vs[cur.x][cur.y] == 'M')
// //     return false;
// //   if (dist > ans)
// //     return false;
// //   if (vs[cur.x][cur.y] == 'E')
// //     return true;
// //   vs[cur.x][cur.y] = 'M';
// //   bool found = false;
// //   found |= dfs(cur + DIRXY[dir], dir, dist + 1);
// //   found |= dfs(cur + DIRXY[(dir + 1) % 4], (dir + 1) % 4, dist + 1001);
// //   found |= dfs(cur + DIRXY[(dir + 3) % 4], (dir + 3) % 4, dist + 1001);
// //   if (!found)
// //     vs[cur.x][cur.y] = '.';
// //   else
// //     vs[cur.x][cur.y] = 'O';
// //   return found;
// // }

// void part2() {
//   map<pair<Point<int>, int>, pair<UST<int>, ULL>> vis;
//   priority_queue<tuple<ULL, Point<int>, int>, vector<tuple<ULL, Point<int>, int>>, greater<>> q;
//   q.emplace(0, start, 1);
//   while (!q.empty()) {
//     Point<int> cur = get<1>(q.top());
//     int dir = get<2>(q.top());
//     ULL dist = get<0>(q.top());
//     q.pop();
//     if (vs[cur.x][cur.y] == '#')
//       continue;
//     if (dist > ans)
//       break;
//     if (HAS(vis, mp(cur, dir)))
//     {
//       if(dist == vis[{cur,dir}].second)
//         vis[{cur, dir}].first.insert(dir);
//       else if(dist < vis[{cur,dir}].second)
//       {
//         vis[{cur, dir}].first.clear();
//         vis[{cur, dir}].first.insert(dir);
//         vis[{cur, dir}].second = dist;
//       }
//       else
//         continue;
//     }
//     else
//     {
//       vis[{cur, dir}].first.insert(dir);
//       vis[{cur, dir}].second = dist;
//     }
//     Point<int> nxt = cur + DIRXY[dir];
//     q.emplace(dist + 1, nxt, dir);
//     q.emplace(dist + 1001, cur + DIRXY[(dir + 1) % 4], (dir + 1) % 4);
//     q.emplace(dist + 1001, cur + DIRXY[(dir + 3) % 4], (dir + 3) % 4);
//   }
//   queue<pair<Point<int>, int>> qq;
//   REP(i, 4)
//     qq.emplace(epos, i);
//   while(!qq.empty())
//   {
//     Point<int> curr = qq.front().first;
//     int dir = qq.front().second;
//     qq.pop();
//     vs[curr.x][curr.y] = 'O';
//     EACH(dir, (vis[{curr, dir}].first))
//     {
//       // qq.push(curr + DIRXY[dir]);
//       print(dir);
//     }
//   }
// }

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();
  return 0;
}
