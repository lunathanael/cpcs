#include <iostream>
#include <string>

using namespace std;

int main() {

	int inputNumber;
	cin >> inputNumber;


	for (int i = 0; i < inputNumber; ++i) {
		string input;
		cin >> input;

		bool isPalidrome = false;

		if (input.length() % 2 == 0) {
			//even
			if (input.length() <= 3) {
				isPalidrome = false;
			}
			else {
				char record = input.at(0);
				for (int j = 1; j < (input.length() / 2); ++j) {
					if (record == input.at(j)) {
						continue;
					}
					else {
						isPalidrome = true;
					}
				}
			}
		}
		else {
			//odd
			char record = input.at(0);
			for (int j = 1; j < (input.length() / 2); ++j) {
				if (record == input.at(j)) {
					continue;
				}
				else {
					isPalidrome = true;
				}
			}
		}

		if (isPalidrome) {
			cout << "yes" << endl;
		}
		else {
			cout << "no" << endl;
		}
	}

	return 0;



	// if even, all numbers must be even
	return 0;
}