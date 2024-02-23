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
    int N;
    cin >> N;

    ll dec = 0;
    ll inc = 0;
    ll change = 0;
    for(int i = 0; i < N; ++i)
    {
        ll level;
        cin >> level;
        level += change;
        if(level != 0)
        {
            if(level > 0)
            {
                dec += level;
            }
            else
            {
                inc -= level;
            }
            change -= level;
        }
        change += (inc - dec);
    }
    cout << (inc + dec) << endl;
    return 0;
}