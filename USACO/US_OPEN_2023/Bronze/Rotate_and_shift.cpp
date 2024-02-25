#include <iostream>

using namespace std;

int main() {
	int N, K, T;

	cin >> N >> K >> T;

	int cow_map[N] = { 0 };

	for (int i = 0; i < N; ++i) {
		cow_map[i] = i;
	}

	int swap_index[K] = { 0 };
	for (int i = 0; i < K; ++i) {
		cin >> swap_index[i];
	}

	for (int t = 0; t < T; ++t) {

		cout << cow_map[0];
		for (int i = 1; i < N; ++i) {
			cout << ' ' << cow_map[i];
		}
		cout << endl;
		// swapping step
		int temp = cow_map[swap_index[K - 1]];
		for (int i = K - 1; i > 0; --i) {
			cow_map[swap_index[i]] = cow_map[swap_index[i - 1]];
		}
		cow_map[swap_index[0]] = temp;


		// increasing swapping
		for (int i = 0; i < K; ++i) {
			++swap_index[i];
			if (swap_index[i] == N) {
				swap_index[i] = 0;
			}
		}
	}






	return 0;
}