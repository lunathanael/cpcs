#include <iostream>
#include <algorithm>

using namespace std;


int main() {
	int n, k;
	cin >> n >> k;

	int scores[n] = {};
	for (int contestant = 0; contestant < n; ++ contestant) {
		int score;
		cin >> score;
		scores[contestant] = score;
	}

	sort(scores, scores + n, greater<int>());

	int cutoff = scores[--k];

	int qualify = 0;
	for (int score : scores) {
		if (score >= cutoff && score > 0) {
			++qualify;
		}
		else {
			break;
		}
	}

	cout << qualify;
	return 0;
}