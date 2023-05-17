#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	
	int testCases;
	cin >> testCases;
	int output[testCases];

	for (int testCase = 0; testCase < testCases; ++testCase) {
		int bookNumber;
		cin >> bookNumber;

		int one1BestTime = 2'500'000;
		int one2BestTime = 2'500'000;
		int twoBestTime = 5'000'000;
		for (int book = 0; book < bookNumber; ++book) {
			int time;
			cin >> time;

			string abilities;
			cin >> abilities;
			if (abilities == "00") {
				continue;
			}
			else if (abilities == "10") {
				one1BestTime = min(one1BestTime, time);
			}
			else if (abilities == "01") {
				one2BestTime = min(one2BestTime, time);
			}
			else if (abilities == "11") {
				one1BestTime = min(one1BestTime, time);
				one2BestTime = min(one2BestTime, time);
				twoBestTime = min(twoBestTime, time);
			}
		}
		output[testCase] = min(twoBestTime, (one1BestTime + one2BestTime));
	}

	for (int testCase = 0; testCase < testCases; ++testCase) {
		if (output[testCase] >= 2'500'000) {
			cout << -1 << endl;
			continue;
		}
		cout << output[testCase] << endl;
	}


	return 0;
}