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

int main()
{
    int n; string s;
    cin >> n >> s;
    int rem = 0;
    int prev = 0;
    for(int i = 1; i < static_cast<int>(s.size()); ++i)
    {
        if(s[i] != s[prev])
        {
            prev = i;
        }
        else
        {
            ++rem;
        }
    }
    cout << rem << '\n';
    return 0;
}

