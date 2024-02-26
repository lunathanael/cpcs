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

static constexpr int max_months = 1e4+1;

int N;
int64_t days[max_months];


unordered_set<int64_t> divs;

void input()
{
    cin >> N;
    for(int i = 0; i < N; ++i)
    {
        cin >> days[i];
    }
}

bool can(int64_t L)
{
    
    int64_t a = -1, b = -1, c = -1;
    for(int i = 0; i < N; ++i)
    {
        int64_t mod = days[i] % L;
        if(mod == a || mod == b || mod == c)
            continue;
        if(a == -1)
            a = mod;
        else if (b == -1)
            b = mod;
        else if (c == -1)
            c = mod;
        else
            return 0;
    }
    return 1;
}

void process()
{
    unordered_set<int64_t> days_s;
    for(int i = 0; i < N; ++i)
    {
        days_s.insert(days[i]);
    }

    N = days_s.size();
    int i = 0;
    for(auto & a : days_s)
    {
        days[i++] = a;
    }
    return;

    // unordered_set<int64_t> ust;
    // int i = 0, j = 0;
    // while(i < N)
    // {
    //     if(!ust.count(days[i]))
    //     {
    //         ust.insert(days[i]);
    //         days[j++] = days[i];
    //     }
    //     ++i;
    // }
    // N = j;
}

void process2()
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            int64_t diff = abs(days[j] - days[i]);
            for(int64_t k = 1; k <= 100000; ++k)
            {
                if(diff % k == 0)
                {
                    divs.insert(k);
                    divs.insert(diff / k);
                }
            }
        }
    }
}

int64_t solve()
{
    process();
    int64_t min_ai = 4e9+1;
    for(int i = 0; i < N; ++i)
        min_ai = min(min_ai, days[i]);

    int64_t mn = min_ai / 4;
    if(N <= 3)
    {
        return (mn*(mn+1))/2;
    }

    process2();
    int64_t sum = 0;
    for(const int64_t & L : divs)
    {
        if(L <= mn && can(L))
            sum += L;
    }
    return sum;

}

int main()
{
    // Start here
    input();
    cout << solve() << endl;
    return 0;
}

