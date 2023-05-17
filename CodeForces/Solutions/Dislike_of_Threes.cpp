#include <iostream>


using namespace std;



int main() {
	int cases;
	cin >> cases;

	while (cases--) {
		int index;
		cin >> index;

		int Count = index % 18;
		index /= 18;

		int number = index * 30;
		if (Count == 0) {
			--number;
		}
		else {
			if (Count >= 9) {
				++Count;
				if (Count >= 16) {
					++Count;
				}
			}
			number += Count;
			--Count;
			number += Count / 2;

		}

		cout << number << endl;
	}


	return 0;
}