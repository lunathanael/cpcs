#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int testcases;
    cin >> testcases;

    while (testcases--) {


        string line;
        getline(cin, line);
        remove(line.begin(), line.end(), ' ');

        int string_length = line.length();

        for (int i = 0; i < (string_length / 2); ++i) {
            if (line[i] != line[string_length - 1 - i]) {
                cout << "NO\n";
                goto next;
            }
        }
        cout << "YES\n";
        next:
        continue;
    }
    return 0;
}
