#include <iostream>
#include <algorithm>

using namespace std;


int main() {
	int cases;
	cin >> cases;

	for (int Case = 0; Case < cases; ++Case) {
		int length;
		cin >> length;
		if (length == 1) {
			cout << '1' << endl;
			continue;
		}

		if (length % 2 == 0) {
			for (int i = length; i > 0;) {
				cout << i << ' ';
				--i;
				cout << (length - i) << ' ';
				--i;
			}

			cout << endl;
		}
		else {
			cout << "-1" << endl;
		}
	}

	return 0;
}