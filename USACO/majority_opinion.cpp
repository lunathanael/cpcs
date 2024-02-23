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


int main()
{
    int tests;
    cin >> tests;
    while(tests--)
    {
        int n;
        cin >> n;
        vector<int> cows(n);
        for(int i = 0; i < n; ++i)
        {
            cin >> cows[i];
        }
        set<int>poss;

        for(int i = 0; i < n; ++i)
        {
            vector<int> occ(n+1, 0);
            for(int j = i; j < n; ++j)
            {
                occ[cows[j]]++;
                if(occ[cows[j]] != 1 && occ[cows[j]] > (j-i+1)/2)
                {
                    poss.insert(cows[j]);
                }
            }
        }

        if(poss.empty())
        {
            cout << -1;
        }
        else
        {
            for(auto a = poss.begin(); a != poss.end();)
            {
                cout << (*a);
                advance(a, 1);
                if(a != poss.end())
                    cout << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}