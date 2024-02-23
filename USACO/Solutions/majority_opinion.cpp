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
        vector<vector<int>> cows(n+1, vector<int>{});
        for(int i = 0; i < n; ++i)
        {
            int temp;
            cin >> temp;
            cows[temp].push_back(i);
        }
        vector<int> poss;

        for(int i = 1; i <= n; ++i)
        {
            bool found = false;
            for(int j = 0; !found && j < cows[i].size(); ++j)
            {
                for(int k = j + 1; !found && k < cows[i].size(); ++k)
                {
                    if ((k-j+1)*2 > (cows[i][k] - cows[i][j] + 1))
                    {
                        poss.push_back(i);
                        found=true;
                        break;
                    }
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