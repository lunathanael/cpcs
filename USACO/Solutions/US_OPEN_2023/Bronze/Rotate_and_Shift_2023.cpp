#include <iostream>
#include <algorithm>

using namespace std;


int main() {

	int N, K, T; // cows, positions, time
	cin >> N >> K >> T;
	int cow_map[N];
	int swap_map[K];

	int current_cow_index = 0;
	for (int i = 0; i < K; ++i) {
		cin >> swap_map[i];
	}
	for (int i = 0; i < (K-1); ++i) {
		int cycle_time = swap_map[i + 1] - swap_map[i];
		while (current_cow_index < swap_map[i+1]) {
			int distance = current_cow_index - swap_map[i] + 1;
			int time_cycle = T - distance + cycle_time;
			int cycles = max(0, time_cycle / cycle_time);
			cow_map[((cycles * cycle_time + current_cow_index) % N)] = current_cow_index;
			++current_cow_index;
		}
	}
	int cycle_time = N - swap_map[K-1];
	while (current_cow_index < N) {
		int distance = current_cow_index - swap_map[K - 1] + 1;
		int time_cycle = T - distance + cycle_time;
		int cycles = max(0, time_cycle / cycle_time);
		cow_map[((cycles * cycle_time + current_cow_index) % N)] = current_cow_index;
		++current_cow_index;
	}

	cout << cow_map[0];
	for (int i = 1; i < N; ++i) {
		cout << ' ' << cow_map[i];
	}

	return 0;
}