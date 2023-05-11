#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


string conversation;
int conversationLength;

int excitement = 0;
vector<int> poss;
vector<int> output;

// Possiblities
// NO fs
// 111 101 001 011
//  2   0   1   1
// Sender F only
// 1F1  0F1
// 2,0   1
// double F
// FF1     1FF
// 0,1,2 + count, end   0,1, 2, count + 1
// triple F
// FFF
// 0,1,2, count, poss end


// FF1 Tag 1, end and push, 1FF tag 1, push not end.


// First
// 11x  10x
// +1    +0
// Then
// 1f1  1f0  1ff
// 2,0   +1   +1, c1
// ff1
// 1, +c

void GenerateLevels() {
	output.push_back(excitement);
	if (poss.size() == 0) {
		return;
	}
	if (find(poss.begin(), poss.end(), 1) != poss.end())
	{
		for (int i = 0; i < poss.size(); ++i) {
			if (poss[i] == 1) {
				++excitement;
				output.push_back(excitement);
			}
			else {
				++excitement;
				output.push_back(excitement);
				++excitement;
				output.push_back(excitement);
			}
		}
		// there is a one
	}
	else {
		for (int i = 0; i < poss.size(); ++i) {
			excitement += 2;
			output.push_back(excitement);
		}
	}
}

int main() {
	cin >> conversationLength;
	cin >> conversation;
	int counter = 0;

	char chainStart;
	char sender, prevSender;


	sender = conversation.at(0);

	if (sender == 'F') {
		chainStart = 'N';
	}

	for (int i = 1; i < conversationLength; ++i) {

		prevSender = conversation.at(i - 1);
		sender = conversation.at(i);

		if (sender != 'F') {
			if (sender == prevSender) {
				++excitement;
			}


			else if (prevSender == 'F') {



				if (chainStart == 'N') {
					poss.push_back(1);
					continue;
				}
				else {
					if (counter % 2 == 0) {
						if (sender == chainStart) {
							++excitement;
						}

					}
					else {
						if (sender != chainStart) {
							++excitement;
						}
						else {
							++counter;
						}
					}
					counter = counter / 2;
					for (int i = 0; i < counter; ++ i) {
						poss.push_back(2);
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
		for (int i = 0; i < counter; ++i) {
			poss.push_back(1);
		}
	}


	GenerateLevels();

	cout << output.size() << endl;
	for (int i = 0; i < output.size(); ++i) {
		cout << output[i] << endl;
	}


	return 0;
}





