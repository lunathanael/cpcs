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

void dfs(vector<vector<int>> & edges, vector<vector<int>> & res, vector<int> & occ, int i, int prev=-1)
{
    if(i!=0 && (edges[i].size() == 1 && edges[i][0] == prev))
    {
        res.push_back(occ);
        return;
    }
    for(int & j : edges[i])
    {
        if(j == prev)
            continue;

        occ[j] = 1;
        dfs(edges, res, occ, j, i);
        occ[j] = 0;
    }
}

int hungarian(vector<vector<int>> & A, int n, int m) {
    int INF = 1e6;
    vector<int> u(n + 1, 0), v(m + 1, 0), p(m + 1, 0), way(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = -INF, j1; // Initialize delta to negative infinity for maximization
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    int cur = A[i0 - 1][j - 1] - u[i0] - v[j]; // Adjust indices if needed
                    if (cur > minv[j]) // Change comparison for maximization
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] > delta) // Change comparison for maximization
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] += delta; // Adjust addition for maximization
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return v[0]; // This now represents the maximum value
}


int dfs_res(vector<vector<int>> & paths, vector<int> & potions, int m)
{
    int n = paths.size();
    vector<int> upp(m,0);
    for(int i = 0; i < potions.size(); ++i)
    {
        upp[potions[i]-1] = i;
    }

    for(int j = 0; j < m; ++j)
    {
        if(upp[j] >= n)
        {
            for(int i = 0; i < n; ++i)
            {
                paths[i][j] = 0;
            }
        }
    }

    paths.insert(paths.begin(), vector<int>(m, 0));
    for(int i = 0; i <= n; ++i)
        paths[i].insert(paths[i].begin(), 0);

    return hungarian(paths, n, m);
}

int main()
{
    // Start here
    int N;
    cin >> N;

    vector<int> potions(N);
    for(int i = 0; i < N; ++i)
    {
        cin >> potions[i];
    }

    vector<vector<int>> edges(N);
    for(int i = 0; i < N-1; ++i)
    {
        int a, b;
        cin >> a >> b;
        edges[a-1].push_back(b-1);
        edges[b-1].push_back(a-1);
    }

    vector<int> occ(N, 0);
    vector<vector<int>> res;
    occ[0] = 1;
    dfs(edges, res, occ, 0);

    cout << dfs_res(res, potions, N) << endl;
    return 0;
}

