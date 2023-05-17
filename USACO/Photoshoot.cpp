#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int cowLine;

// G -> even

// Initial guess,
// Corresponding location of cowshift


int main() {
	int cowNumber;
	int index = 0;
	cin >> cowNumber;

	string lineString;
	cin >> lineString;
	for (int i = --cowNumber; i >= 0; --i) {
		if (index >= i) {
			break;
		}
		if (i % 2 == 1) {
			// Even location
			if (lineString.at(i) == 'G') {
				// G cow at even
			}
			else if (lineString.at(i) == 'H') {
				if (lineString.at(index) == 'G') {
					reverse(lineString.begin(), lineString.end());
					//cout << lineString << endl;
					++cowLine;
					continue;
				}
			}
		}
		else {
			// Uneven
			if (lineString.at(i) == 'G') {
				// G cow at odd
				++index;

			}
			else {
				
			}
		}
		lineString.pop_back();
	}


	//1ULL << cowIndex
	cout << cowLine;
	
	int iterations = 0;


	return 0;
}


