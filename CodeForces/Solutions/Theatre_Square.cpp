#include <iostream>

using namespace std;


int main() {
	long long int n, m, a;

	cin >> n >> m >> a;


	if (n % a != 0) {
		n /= a;
		++n;
	}
	else {
		n /= a;
	}
	if (m % a != 0) {
		m /= a;
		++m;
	}
	else {
		m /= a;
	}
	long long int flagstones = (n) * (m);

	cout << flagstones;
	return 0;
}