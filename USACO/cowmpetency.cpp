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

bool satisfies(vector<int> & list, vector<pair<int, int>> & q, const int & Q)
{
    for(int i = 0; i < Q; ++i)
    {
        int a = q[i].first - 1, b = q[i].second - 1;
        int mx1 = 0;
        for(int j = 0; j <= a; ++j)
            mx1 = max(mx1, abs(list[j]));
        int mx2 = 0;
        for(int j = a+1; j < b; ++j)
            mx2 = max(mx2, abs(list[j]));
        if(mx2 > mx1)
            return false;
        if(abs(list[b]) <= mx1)
            return false;
    }
    return true;
}

bool next_ar(vector<int>&list, const int & N, const int & C)
{
    for(int i = N-1; i >= 0; --i)
    {
        if(list[i] < 0 && list[i] != -C)
        {
            --list[i];
            for(int j = i+1; j < N; ++j)
                list[j] = max(list[j], -1);
            return true;
        }
    }
    return false;
}

// problem seems like segmented tree problem, time=O(TQlog(n))
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int N, Q, C;
        cin >> N >> Q >> C;
        vector<int> list(N);
        for(int i = 0; i < N; ++i)
        {
            cin >> list[i];
        }
        vector<pair<int, int>> q(Q);
        for(int i = 0; i < Q; ++i)
        {
            cin >> q[i].first >> q[i].second;
        }
        bool poss = false;

        //
        for(int i = 0; i < N; ++i)
        {
            if(list[i] == 0)
                list[i] = -1;
        }

        do
        {
            if(satisfies(list, q, Q))
            {
                poss = true;
                break;
            }
        }
        while(next_ar(list, N, C));
        //

        if(poss)
        {
            for(int i = 0; i < N; ++i)
            {
                cout << abs(list[i]);
                if(i != N-1)
                    cout << ' ';
            }
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}