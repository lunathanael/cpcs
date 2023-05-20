#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main() {
	string input;

	cin >> input;

	const long int arrSize = (input.length() + 1) / 2;

	int addition[arrSize];

	for (int i = 0; i < arrSize; ++i) {
		addition[i] = (input[i * 2] - '0');
	}

	sort(addition, addition + arrSize);
	for (int number = 0; number < arrSize; ++number) {
		if (number != 0) {
			cout << '+';
		}
		cout << addition[number];
	}
	cout << endl;

	return 0;
}