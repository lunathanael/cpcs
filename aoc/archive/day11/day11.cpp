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
LL ans1{0}, ans2{0};
VS vnums;

void process() {

  string s;
  stringstream ss(vs[0]);
  while (getline(ss, s, ' ')) {
    vnums.pb(s);
  }
}


string operator*(const string& num, LL multiplier) {
    string result;
    LL carry = 0;
    LL n = SZ(num);
    
    REPR(i, n-1) {
        LL digit = num[i] - '0';
        LL product = digit * multiplier + carry;
        carry = product / 10;
        result = SCAST(char,product % 10 + '0') + result;
    }
    
    while (carry) {
        result = SCAST(char,carry % 10 + '0') + result;
        carry /= 10;
    }
    
    return result;
}



void part1() {
    VS vvs = vnums;
    VS next;
    REP(blink, 25) {
        next.clear();
        EACH(const &num, vvs) {
            if (num == "0") {
                next.eb("1");
                continue;
            }

            int digits = SZ(num);

            if (even(digits)) {
                int mid = digits / 2;
                string left = num.substr(0, mid);
                string right = num.substr(mid);
                next.pb(left);
                while (right.size() > 1 && right[0] == '0') {
                    right = right.substr(1);
                }
                next.pb(right);

            }
            else {
                next.pb(num * 2024LL);
            }
        }
        vvs = next;
    }

    ans1 = SZ(vvs);
    print("ans1:", ans1);
}

void part2() {
    UMP<string, LL> ump;
    EACH(num, vnums) {
        ump[num]++;
    }
    REP(blink, 75) {
        UMP<string, LL> next;
        EACH(p, ump)   {
            string num = p.first;
            LL count = p.second;
            if (num == "0") {
                next["1"] += count;
                continue;
            }

            int digits = SZ(num);

            if (even(digits)) {
                int mid = digits / 2;
                string left = num.substr(0, mid);
                string right = num.substr(mid);
                while (right.size() > 1 && right[0] == '0') {
                    right = right.substr(1);
                }
                next[left] += count;
                next[right] += count;

            }
            else {
                next[num * 2024LL] += count;
            }
        }
        ump = next;
    }

    EACH(p, ump) {
        ans2 += p.second;
    }
    print("ans2:", ans2);
}

int main() {
  IOSOPT;
  // Start here
  process();
  part1();
  part2();

  return 0;
}
