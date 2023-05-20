#include <iostream>
#include <string>


using namespace std;


int main() {
	string input;
	cin >> input;

	bool nonZero = false;
	for (int i = 0; i < input.length(); ++i) {
		if (input[i] == '.') {
			if (nonZero) {
				cout << 1;
				nonZero = false;
			}
			else {
				cout << 0;
			}
			continue;
		}
		else {
			if (nonZero) {
				cout << 2;
				nonZero = false;
			}
			else {
				nonZero = true;
			}
		}
	}

	return 0;
}