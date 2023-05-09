#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

bool compare(const pair<int, bool>& p1, const pair<int, bool>& p2) {
	return ((p1.first < p2.first) || ((p1.first == p2.first ) && ( p2.second)) ) ;
}


int main() {
	int cowNumber;
	cin >> cowNumber;

	pair <int, bool> cowClaims[cowNumber];

	int greaters = 0;

	bool direction;
	char character;
	int location;
	for (int i = 0; i < cowNumber; ++i) {
		cin >> character;
		cin >> location;
		if (character == 'G') {
			direction = true;
		}
		else {
			direction = false;
			++location;
			++greaters;
		}
		cowClaims[i] = { location, direction };
	}

	sort(cowClaims, cowClaims + cowNumber, compare);

	short int cowsAgreeing = greaters;
	short int best = 0;

	for (int i = 0; i < cowNumber; ++i) {
		if (cowClaims[i].second) {
			++cowsAgreeing;
			best = max(cowsAgreeing, best);
		}
		else {
			--cowsAgreeing;
		}
	}
	cout << cowNumber - best;

	return 0;
}




