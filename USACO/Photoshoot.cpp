#include <iostream>
#include <string>

using namespace std;

int cowLine;

// G -> even

bool IsAesthetic() {

}

// Initial guess,
// Corresponding location of cowshift


int main() {
	int cowNumber;
	cin >> cowNumber;

	string lineString;
	cin >> lineString;

	for (int i = cowNumber - 1; i >= 0; ++i) {
		if (i % 2 == 1) {
			// Even location
			if (lineString.at(i) == 'G') {
				// G cow at even
			}
		}
		else {
			// Uneven
			if (lineString.at(i) == 'G') {
				// G cow at even
			}
		}
	}


	//1ULL << cowIndex
	cout << cowLine;
	
	int iterations = 0;


	return 0;
}


