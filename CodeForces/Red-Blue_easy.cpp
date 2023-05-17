#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int maxMin(int c[], int eleInArray)
{
	int b[eleInArray];
	copy(c, c + eleInArray, b);

	int query;
	cin >> query;


	bool inc = true;
	while (query >= eleInArray) {
		// increase function
		if (inc) {
			for (int i = 0; i < eleInArray; ++i) {
				b[i] += query--;
			}
			inc = false;
			cout << "inc";
		}

		else {
			//decrease function
			for (int i = eleInArray - 1; i >= 0; --i) {
				b[i] -= query--;
			}
			inc = true;
			cout << "dec";
		}
		sort(b, b + eleInArray);
	}
	if (query > 0) {
		cout << "query: " << query;
		if (inc) {
			for (int i = 0; query > 0; ++i) {
				b[i] += query--;
			}
		}

		else {
			//decrease function
			for (int i = eleInArray - 1; query > 0; --i) {
				b[i] -= query--;
			}
		}
		sort(b, b + eleInArray);
	}
	cout << "\nfinal: ";
	for (int h : b) {
		cout << h << ' ';
	}
	cout << endl;
	return b[0];
}

int main() {
	int eleInArray;
	cin >> eleInArray;

	int queries;
	cin >> queries;

	int b[eleInArray];

	for (int ele = 0; ele < eleInArray; ++ele) {
		int element;
		cin >> element;	
		b[ele] = element;
	}


	sort(b, b + eleInArray);


	cout << "\nInitial: ";
	for (int h : b) {
		cout << h << ' ';
	}
	cout << endl;

	for (int ele = 1; ele <= queries; ++ele) {
		cout << maxMin(b, eleInArray) << ' ';
	}


	return 0;
}