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

void solve()
{
    int N, Q, C;
    cin >> N >> Q >> C;
    vector<int> list(N+1, 0);
    for(int i = 1; i <= N; ++i)
    {
        cin >> list[i];
    }
    vector<int> B(N+1, 0);
    for(int i = 0; i < Q; ++i)
    {
        int a_i, h_i;
        cin >> a_i >> h_i;
        B[a_i] = h_i;
    }

    vector<char> assigned(N+1, 1);
    for(int i = 1; i <= N; ++i)
    {
        if(list[i] == 0)
        {
            list[i] = 1;
            assigned[i] = 0;
        }
    }

    // Check conditions for B
    for (int i = 1; i <= N; ++i)
    {
        // Ensure that every j such that i < j < B[i] has B[j] = B[i]
        for(int j = i; j < B[i]; ++j)
        {
            if(B[j] != 0 && B[j] != B[i])
            {
                cout << -1 << endl;
                return;
            }
            B[j] = B[i];
        }
    }

    for(int i = 1; i <= N; ++i)
    {
        if(B[i] == 0)
        {
            continue;
        }
        int mx_before = *max_element(list.begin(), list.begin() + i + 1);
        int mx_after = *max_element(list.begin(), list.begin() + B[i]);

        if (mx_after > mx_before)
        {
            bool assignment_found = false;
            for(int j = i; j > 0; --j)
            {
                if(B[j] != 0 && B[j] < B[i])
                {
                    cout << -1 << endl;
                    return;
                }
                if(assigned[j])
                {
                    continue;
                }
                list[j] = mx_after;
                assignment_found = true;
                break;
            }
            if(assignment_found == false)
            {
                cout << -1 << endl;
                return;
            }
            mx_before = mx_after;
        }
        if (!assigned[B[i]])
        {
            list[B[i]] = mx_before + 1;
        }
        if (list[B[i]] <= mx_before)
        {
            cout << -1 << endl;
            return;
        }
    }

    if(any_of(list.begin(), list.end(), [&](const int & i)
    {
        return i > C;
    }))
    {
        cout << -1 << endl;
        return;
    }

    for(int i = 1; i <= N; ++i)
    {
        cout << list[i];
        if(i != N)
        {
            cout << ' ';
        }
    }
    cout << endl;
}

// problem seems like segmented tree problem, time=O(TQlog(n))
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        solve();
    }

    return 0;
}