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

static constexpr bool JUMP_PAD = 0;

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
    int N, S;
    cin >> N >> S;
    vector<pair<int, bool>> loc(N+1);
    for(int i = 1; i <= N; ++i)
    {
        int sign, val;
        cin >> sign >> val;
        loc[i] = {val, sign};
    }

    ll bpower = 1;
    ll bloc = S;

    int broken = 0;

    vector<pair<ll, ll>> dp(N+1, make_pair(0, 0));

    while(bloc >= 1 && bloc <= N)
    {
        bool direction = bpower > 0;
        if(direction)
        {
            if(dp[bloc].first == bpower)
            {
                break;
            }
            dp[bloc].first = bpower;
        }
        else
        {
            if(dp[bloc].second == bpower)
            {
                break;
            }
            dp[bloc].second = bpower;
        }
        if(loc[bloc].second == JUMP_PAD)
        {
            if(direction)
            {
                bpower += loc[bloc].first;
            }
            else
            {
                bpower -= loc[bloc].first;
            }
            bpower *= -1;
        }
        else
        {
            
            if(loc[bloc].first != -1 && loc[bloc].first <= abs(bpower))
            {
                loc[bloc].first = -1;
                ++broken;
            }
        }
        bloc += bpower;
    }

    cout << broken << endl;
    return 0;
}