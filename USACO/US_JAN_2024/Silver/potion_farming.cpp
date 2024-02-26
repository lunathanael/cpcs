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

static constexpr int MAXN = static_cast<int>(1e5 + 1);

int N;
vector<int> adj[MAXN];
int potions[MAXN];
int reachable[MAXN];

int C_i[MAXN];

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

int dfs(int v, int parent = 0)
{
    if(adj[v].size() == 1 && v != 1)
    {
        C_i[v] = 1;
        return 1;
    }
    int sum = 0;
    for(auto & u : adj[v])
    {
        if(u != parent)
        {
            sum += dfs(u, v);
        }
    }
    return C_i[v] = sum;
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


int solve1(int v, int parent = 0)
{

    int sum = reachable[v];
    for(int & u : adj[v])
    {
        if(parent != u)
        {
            sum += solve1(u, v);
        }
    }
    return min(sum, C_i[v]);
}

int main()
{
    // Start here
    input();
    process();
    dfs(1);
    cout << solve1(1) << endl;
    return 0;
}

