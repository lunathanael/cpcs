#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
#include<cassert>
#include <cmath>
#include <chrono>
#include<cstring>

using namespace std;

#define ll long long int

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
    // Start here
    int tc;
    cin >> tc;
    while (tc--) {
        int n, x;
        cin >> n >> x;

        if (x == 0 && n == 1) {
            cout << -1 << '\n';
        } else {
            int a = __builtin_popcount(x);
            if (a > n) {
                cout << x << '\n';
            } else {
                if ((n-a) % 2 == 0 || a > 1 || (a == 1 && x % 2 == 0))
                {
                    cout << x + (n-a + 1) / 2 * 2 << '\n';
                }
                else
                {
                    cout << x + (n-a - 1) + 4 << '\n';
                }
            }
        }
        
    }

    return 0;
}

