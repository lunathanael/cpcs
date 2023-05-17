#include <iostream>
#include <vector>

using namespace std;

int isIncreasing(int a, int b) {
	if (a < b) {
		return 1;
	}
	else if (a == b) {
		return 0;
	}
	return -1;
}

int main() {
	int testCases;
	cin >> testCases;

	for (int i = 0; i < testCases; ++i) {
		int arraySize;
		cin >> arraySize;
		
		vector<int> a;
		int prev = -1;
		bool deleted = false;
		// Cin array, removing duplicates
		for (int j = 0; j < arraySize; ++j) {
			int curr;
			cin >> curr;
			if (curr == prev) {
				continue;
			}
			else {
				prev = curr;
				a.push_back(curr);
			}


		}

		if (deleted) {
			a.push_back(prev);
		}


		// check for equal difference
		//traverse array
		int increasing = isIncreasing(a[0], a[1]);
		vector<int> output;
		output.push_back(a[0]);
		for (int j = 1; j < a.size() - 1; ++j) {
			int temp = isIncreasing(a[j], a[j + 1]);
			if (increasing == temp) {
				continue;
			}
			else {
				increasing = temp;
				output.push_back(a[j]);
			}
		}
		output.push_back(a.back());

		if (output.size() == 2 && output[0] == output[1]) {
			cout << 1 << endl;
			continue;
		}
		else {
			cout << output.size() << endl;
			continue;
		}

		for (int j = 0; j < output.size(); ++j) {
			cout << ' ' << output[j];
		}
		cout << endl;


	}

	return 0;
}