#include <iostream>
#include <algorithm>

using namespace std;


int main() {
	int cases;
	cin >> cases;
	while (cases--) {
		int elements;
		cin >> elements;

		//sums:
		long long int neg = 0;// starts neg
		long long int pos = 0;

		int poslen = 0;
		int neglen = 0;

		// flag
		bool isneg = true;
		bool ispos = true;

		long long int negMax = -10'000'000'000;
		long long int posMax = -10'000'000'000;

		for (int index = 0; index < elements; ++index) {
			long long int number; cin >> number;
			if (number > 0) {
				if (ispos) {
					if (posMax != -10'000'000'000) {
						pos += posMax;
					}
					posMax = number;
					ispos = false;
					++poslen;
				}
				else {
					posMax = max(number, posMax);
				}
				if (!isneg) {
					neg += negMax;
					negMax = number;
					isneg = true;
					++neglen;
				}
				else {
					negMax = max(number, negMax);
				}
			}
			else {
				if (isneg) {
					if (negMax != -10'000'000'000) {
						pos += negMax;
					}
					negMax = number;
					isneg = false;
					++neglen;
				}
				else {
					negMax = max(negMax, number);
				}
				if (!ispos) {
					pos += posMax;
					posMax = number;
					ispos = true;
					++poslen;
				}
				else {
					posMax = max(posMax, number);
				}
			}
		}

		if (negMax != -10'000'000'000) {
			neg += negMax;
		}
		if (posMax != -10'000'000'000) {
			cout << pos << '+';
			cout << posMax << 's' << endl;
			pos += posMax;
		}
		cout << poslen << ' ' << neglen << endl;

		cout << pos << neg << endl;
		if (poslen > neglen) {
			cout << pos << endl;
		}
		else if (poslen == neglen) {

			cout << max(neg, pos) << endl;
		}
		else {
			cout << neg << endl;
		}


	}
	return 0;
}