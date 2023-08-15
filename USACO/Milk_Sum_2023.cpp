#include <iostream>
#include <algorithm>

using namespace std;


long long int calculate(int arr[], int n) {
	long long int total = 0;
	for (long long int i = 0; i < n;) {
		total += (long long int)((long long int)arr[i++] * (long long int)(i));
	}
	return total;
}

int main() {
	int N;
	cin >> N;

	int cows[N];
	for (int i = 0; i < N; ++i) {
		cin >> cows[i];
	}

	int Q;
	cin >> Q;
	for (int a = 0; a < Q; ++a) {
		int temp[N];
		copy(cows, cows + N, temp);
		int i, j;
		cin >> i >> j;
		temp[i-1] = j;
		sort(temp, temp+N);
		cout << calculate(temp, N) << "\n";
	}

	return 0;
}