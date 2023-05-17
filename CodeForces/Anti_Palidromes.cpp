#include <iostream>

using namespace std;


int main() {
	int testCases = 0;
	cin >> testCases;

	for (int cases = 0; cases < testCases; ++cases) {
		int length;
		cin >> length;

		string input;
		cin >> input;
		

		if (length % 2 == 1) {
			cout << "-1\n";
			continue;
		}

		int charArray[26] = {};
		int duplicates = 0;

		for (int character = 0; character < (length / 2); ++character) {
			++charArray[input[character] - 'a'];
			if (input[character] == input[length - character - 1]) {
				++duplicates;
			}
		}
		for (int character = ((length + 1) / 2 ); character < length; ++character) {
			++charArray[input[character] - 'a'];
		}

		int cumm = 0;
		++duplicates;
		for (int charara : charArray) {
			if (charara > length / 2) {
				duplicates = -2;
				break;
			}
			else {
				cumm += charara;
			}
			if (cumm >= length / 2) {
				break;
			}
		}

		cout << (duplicates / 2) << endl;


		// character >= half
	}


	return 0;
}