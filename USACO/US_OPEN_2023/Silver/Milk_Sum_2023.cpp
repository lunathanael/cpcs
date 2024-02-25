#include <bits/stdc++.h>
using namespace std;
typedef long long u64;

const int MAX_SIZE = 1.5e5 + 10;

int i_order[MAX_SIZE], i_index_sorted[MAX_SIZE];
u64 cows[MAX_SIZE], pref[MAX_SIZE];
u64 total_milk = 0;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> cows[i];
	}
	iota(i_order, i_order + N, 0);
	sort(i_order, i_order + N, [&](int i, int j) {
		return cows[i] < cows[j];
		});
	sort(cows, cows + N);
	pref[0] = 0;
	for (int i = 0; i < N;) {
		i_index_sorted[i_order[i]] = i;
		pref[i + 1] = pref[i] + cows[i];
		total_milk += (cows[i] * ++i);
	}

	// search
	int Q;
	cin >> Q;
	while (Q--) {
		int original_index; u64 new_value;
		cin >> original_index >> new_value; --original_index;
		int index_in_cows = i_index_sorted[original_index];
		u64 original_value = cows[index_in_cows];

		u64 output = total_milk;
		int new_index = lower_bound(cows, cows + N, new_value) - cows - (bool)(new_value > original_value);
		output += ( (new_index + 1) * (new_value) ) - ( (index_in_cows + 1) * (original_value) );
		if (new_index > index_in_cows) {
			output -= (pref[new_index + 1] - pref[index_in_cows + 1]);
		}
		else {
			output += (pref[index_in_cows] - pref[new_index]);
		}
		cout << output << '\n';
	}


	return 0;
}