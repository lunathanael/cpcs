#include <iostream>
#include <math.h>


using namespace std;


int main() {
	int row = 6;
	int column;
	while (-- row) {
		column = 6;
		while (-- column) {
			int number; cin >> number;
			if (number) {
				goto calculations;
			}
		}
	}

	calculations:
	cout <<  (abs(3 - row) + abs(3 - column));
	return 0;
}