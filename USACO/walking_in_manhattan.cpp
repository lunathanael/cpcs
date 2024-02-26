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

static constexpr int MAX_Q = 2e5+1, MAX_N = 2e5+1;
int N, Q;
int roads_h[MAX_N], roads_v[MAX_N];
int cows[MAX_Q][3];

void input()
{
    cin >> N >> Q;
    for(int i = 0; i < N; ++i)
    {
        char dir;
        cin >> dir;
        int loc;
        cin >> loc;
        if (dir == 'V')
            roads_v[loc]++;
        else
            roads_h[loc]++;
    }
    for(int i = 0; i < Q; ++i)
    {
        int x, y, d;
        cin >> x >> y >> d;
        cows[i][0] = x;
        cows[i][1] = y;
        cows[i][2] = d;
    }
}

void print_cows()
{
    for(int i = 0; i < Q; ++i)
    {
        cout << cows[i][0] << ' ' << cows[i][1] << endl;
    }
}

void solve_cow(int i)
{
    int walking = 0;
    while(cows[i][2] > walking)
    {
        int& x = cows[i][0], &y = cows[i][1];
        if(roads_h[y] && roads_v[x])
        {
            if(walking%2)
            {
                ++x;
            }
            else
            {
                ++y;
            }
        }
        else if(roads_h[y])
        {
            ++x;
        }
        else
        {
            ++y;
        }
        ++walking;
    }
}

void solve()
{
    for(int i = 0; i < Q; ++i)
    {
        solve_cow(i);
    }
}

int main()
{
    // Start here
    input();
    solve();
    print_cows();
    return 0;
}

