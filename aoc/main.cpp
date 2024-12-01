#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <sstream>
#include <queue>
#include <functional>
#include <sstream>
#include <cassert>
#include <cmath>
#include <chrono>
#include <cstring>

/* START OPTIONAL INCLUDES */
#include "lib/macros.hpp"
/* END OPTIONAL INCLUDES */

using namespace std;

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        if (hash1 != hash2) {
            return hash1 ^ hash2;              
        }
          return hash1;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // Start here

    vector<int> v1, v2;
    // vl v1;
    // vl v2;
    // LL i;
    // while(cin >> i)
    // {
    //     v1.pb(i);
    //     cin >> i;
    //     v2.pb(i);
    // }

    // SORT(v1);
    // SORT(v2);
    
    // LL ans = 0;
    // FOR(i, 0, v1.size())
    // {
    //     ans += abs(v1[i] - v2[i]);
    // }

    // cout << ans << endl;
    return 0;
}

