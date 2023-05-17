#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main() {
	int number;
	cin >> number;
	
	int input;
	for (int i = 0; i < number; ++i) {
		int inputNumber;
		cin >> inputNumber;


		int zeros = 0;
		int bestZeros = 0;
		for (int j = 0; j < inputNumber; ++j) {
			cin >> input;
			if (input == 0) {
				++zeros;
			}
			else {
				zeros = 0;
			}
			bestZeros = max(bestZeros, zeros);
		}
		cout << bestZeros << endl;
	}


	return 0;
};

