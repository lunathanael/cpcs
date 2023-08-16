#include <bits/stdc++.h>

using namespace std;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	unsigned long long int N;
	cin >> N;
	++N;

	unsigned long long int original_order[N] = { 0 };
	unsigned long long int milk_index[N];
	milk_index[0] = 0;
	for (int i = 1; i < N; i++) {
		unsigned long long int value;
		cin >> value;
		original_order[i] = value;
		milk_index[i] = value;
	}
	sort(milk_index, milk_index + N);

	unsigned long long int initial_total = 0;
	for (unsigned long long int i = 1; i < N; ++i) {
		initial_total += (unsigned long long)(milk_index[i] * i);
	}

	
	int Q;
	cin >> Q;
	for (int a = 0; a < Q; ++a) {
		// find replaced, see difference
		unsigned long long int new_total = initial_total;
		unsigned long long int i, new_value;
		cin >> i >> new_value;
		unsigned long long int original_value = original_order[i];

		// find direction
		if (new_value > original_value) {

			//find location
			unsigned long long int x = 1;
			for (; x < N; ++x) {
				if (milk_index[x] == original_value) {
					break;
				}
			}

			new_total -= (unsigned long long)(original_value * x);
			++x;
			while (x < N) {
				if (new_value > milk_index[x]) {
					new_total -= milk_index[x];
					++x;
					continue;
				}
				break;
			}
			--x;
			new_total += (unsigned long long)(new_value * x);
		}
		else if (new_value < original_value) {

			//find location
			unsigned long long int x = 1;
			for (; x < N; ++x) {
				if (milk_index[x] == original_value) {
					break;
				}
			}

			new_total -= (unsigned long long)(original_value * x);
			--x;
			while (x > 0) {
				if (new_value < milk_index[x]) {
					new_total += milk_index[x];
					--x;
					continue;
				}
				break;
			}
			++x;
			new_total += (unsigned long long)(new_value * x);
		}
		cout << new_total << "\n";
	}

	return 0;
}