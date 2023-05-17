#include <iostream>
#include <string>
#include <cctype>

using namespace std;


int main() {
	string first; cin >> first;
	string second; cin >> second;

	int output = 0;
	for (int i = 0; i < first.length(); ++i) {
		first[i] = tolower(first[i]);
		second[i] = tolower(second[i]);
		if (first[i] == second[i]) {
			continue;
		}
		else {
			if (first[i] > second[i]) {
				output = 1;
			}
			else if (first[i] != second[i]) {
				output = -1;
			}
			break;
		}
	}
	cout << output << endl;
	return 0;
}