#include <iostream>
#include <string>


using namespace std;


int main() {
	int statements; cin >> statements;

	int x = 0;
	while (statements--) {
		string command; cin >> command;
		if (command[1] == '-') {
			--x;
		}
		else {
			++x;
		}
	}
	cout << x;
	return 0;
}