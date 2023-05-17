#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstring>

using namespace std;

int main() {
	int testCases;
	cin >> testCases;
	long long int output[testCases];


	for (int i = 0; i < testCases; ++i) {
		int elementCount;
		cin >> elementCount;

		int operationCount;
		cin >> operationCount;

		vector<long int> aarray;
		for (int j = 0; j < elementCount; ++j) {
			long int in;
			cin >> in;
			aarray.push_back(in);
		}
		sort(aarray.begin(), aarray.end());

		//long long int bestSum = search(aarray, operationCount);

		long long int totalSum = accumulate(aarray.begin(), aarray.end(), 0LL);

		long long int partialSum = accumulate(aarray.end() - operationCount, aarray.end(), 0LL);
		long long int bestSum = partialSum;
		//long long int partialSum = 0;


		for (int j = 0; j < operationCount; ++j) {
			int bottomCount = 2 * j;
			int topCount = operationCount - j;
			partialSum -= aarray[elementCount - topCount];

			partialSum += aarray[bottomCount];
			partialSum += aarray[bottomCount + 1];

			bestSum = min(partialSum, bestSum);

		}
		output[i] = totalSum - bestSum;

	}

	for (int i = 0; i < testCases; ++i) {
		cout << output[i] << endl;
	}


	return 0;
}