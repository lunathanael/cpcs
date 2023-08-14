/* CODE BY: Jonathen Chen */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int connections = 0;
int mx = -1;
vector<string> ans;
set<string> st;
map <string, bool> visited;
map <string, vector<string>> mp;
int n, m, k;
//add b to a

void reset() {
    for (auto val : st) {
        visited[val] = false;
    }
}
void addToMap(string a, string b) {
    if (mp.count(a)) {
        mp[a].push_back(b);
    }
    else {
        mp[a] = vector<string>();
        mp[a].push_back(b);
        visited[a] = false;
    }
}

void dfs(string* node, int ctr) {
    //cout << *node << "\n";
    if (visited[*node] || ctr > k) {
        --ctr;
        return;
    }
    visited[*node] = true;
    ++connections;
    for (auto val : mp[*node]) {
        dfs(&val, ctr + 1);
    }
    --ctr;
}

int main() {
    cin >> n >> k >> m;
    for (int i = 0; i < m; ++i) {
        string a, b; cin >> a >> b;
        addToMap(a, b);
        addToMap(b, a);
        st.insert(a);
        st.insert(b);
    }
    for (auto val : st) {
        connections = 0;
        reset();
        dfs(&val, 0);
        --connections;
        if (connections == mx) {
            ans.push_back(val);
        }
        else if (connections > mx) {
            mx = connections;
            ans.clear();
            ans.push_back(val);
        }
    }
    sort(ans.begin(), ans.end());
    for (auto val : ans) {
        cout << val << endl;
    }
    return 0;
}
