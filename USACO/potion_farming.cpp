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

static constexpr int MAXN = static_cast<int>(2e5);

int N;
vector<int> adj[MAXN];
int parent[MAXN];
int potions[MAXN];
int reachable[MAXN];

void input()
{
    cin >> N;
    for(int i = 0; i < N; ++i)
    {
        cin >> potions[i];
    }
    for(int i = 1; i < N; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

void dfs(int v)
{
    for(auto & u : adj[v])
    {
        if(u != parent[v])
        {
            parent[u] = v;
            dfs(u);
        }
    }
}

void process()
{
    int leaves = 0;
    for(int i = 2; i <= N; ++i)
    {
        leaves += adj[i].size() == 1;
    }
    for(int i = 0; i < leaves; ++i)
    {
        reachable[potions[i]]++;
    }
}

bool grab(int v)
{
    while(v>0)
    {
        if(reachable[v] > 0)
        {
            reachable[v]--;
            return 1;
        }
        v = parent[v];
    }
    return 0;
}

int solve()
{
    int pots = 0;
    for(int i = 2; i <= N; ++i)
    {
        if(adj[i].size() == 1)
        {
            pots += grab(i);
        }
    }
    return pots;
}

int main()
{
    // Start here
    input();
    process();
    dfs(1);
    cout << solve() << endl;
    return 0;
}

