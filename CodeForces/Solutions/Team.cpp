#include <iostream>


using namespace std;


int main() {
	int problemNumber;
	cin >> problemNumber;

	int solved = 0;

	for (int problem = 0; problem < problemNumber; ++problem) {
		bool one;
		cin >> one;
		bool two;
		cin >> two;
		bool three;
		cin >> three;


		if (one && two) {
			++solved;
		}
		else {
			if (!three) {
				continue;
			}
			else if (one || two) {
				++solved;
			}
		}
		
	}
	cout << solved << endl;



	return 0;
}