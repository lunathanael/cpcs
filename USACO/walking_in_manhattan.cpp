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
vector<int> roads[2];
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
            roads[0].push_back(loc);
        else
            roads[1].push_back(loc);
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

void proc()
{
    sort(roads[0].begin(), roads[0].end());
    sort(roads[1].begin(), roads[1].end());
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
    int& x = cows[i][0], &y = cows[i][1];
    auto a = lower_bound(roads[0].begin(), roads[0].end(), x);
    auto b = lower_bound(roads[1].begin(), roads[1].end(), y);
    if(*a != x || *b != y)
    {
        if(*a == x)
        {
            int new_y = y + cows[i][2] - walking;
            if(b != roads[1].end())
                new_y = *b;

            int dist = new_y - y;
            dist = min(dist, cows[i][2] - walking);
            walking += dist;
            y += dist;
        }
        else if(*b == y)
        {
            int new_x = x + cows[i][2] - walking;
            if(a != roads[0].end())
                new_x = *a;

            int dist = new_x - x;
            dist = min(dist, cows[i][2] - walking);
            walking += dist;
            x += dist;  
        }
    }

    while(cows[i][2] > walking)
    {
        if(walking % 2 == 0)
        {
            ++b;

            int new_y = y + cows[i][2] - walking;
            if(b != roads[1].end())
                new_y = *b;

            int dist = new_y - y;
            dist = min(dist, cows[i][2] - walking);
            walking += dist;
            y += dist;
        }
        else
        {
            ++a;

            int new_x = x + cows[i][2] - walking;
            if(a != roads[0].end())
                new_x = *a;

            int dist = new_x - x;
            dist = min(dist, cows[i][2] - walking);
            walking += dist;
            x += dist;
        }

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
    proc();
    solve();
    print_cows();
    return 0;
}

