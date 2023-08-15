#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


string conversation;
int conversationLength;

int excitement = 0;
int possExc = 0;

bool canCount = false;



int main() {
	cin >> conversationLength;
	cin >> conversation;
	int counter = 0;

	char chainStart;
	char sender, prevSender;


	chainStart = 'N';
	sender = conversation.at(0);

	for (int i = 1; i < conversationLength; ++i) {

		prevSender = sender;
		sender = conversation.at(i);

		if (sender != 'F') {
			if (sender == prevSender) {
				++excitement;
			}

			else if (prevSender == 'F') {

				if (chainStart == 'N') {
					++possExc;
					canCount = true;
					continue;
				}
				else {
					possExc += counter;
					if (counter % 2 == 0) {
						if (sender == chainStart) {
							++excitement;
						}

					}
					else {
						if (sender != chainStart) {
							++excitement;
							--possExc;
						}
						else {
							++possExc;
						}
					}
				}
			}
			counter = 0;
		}
		else {  //sender == "F"
			++counter;
			if (prevSender != 'F') {
				chainStart = prevSender;
			}
			
		}

	}

	if (sender == 'F') {
		possExc += counter;
		canCount = true;
	}

	int distinct;
	if (canCount) {
		distinct = possExc;
		cout << ++distinct << endl;
		cout << excitement << endl;
		for (int i = 0; i < possExc; ++i) {
			cout << ++excitement << endl;
		}
	}
	else {
		distinct = possExc / 2;
		cout << ++distinct << endl;
		cout << excitement << endl;
		for (int i = 0; i < possExc; i += 2) {
			excitement += 2;
			cout << excitement << endl;
		}
	}
	return 0;
}





