#include <iostream>
#include <string>
#include <vector>

using namespace std;


string conversation;
int conversationLength;

int excitement = 0;
vector<int> poss;

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


int main() {
	cin >> conversationLength;
	cin >> conversation;
	int counter = 0;

	char sender, prevSender, nextSender;


	for (int i = 1; i < convesationLength - 1; ++i) {
		
		prevSender = converstaion.at(i-1);
		sender = conversation.at(i);
		nextSender = conversation.at(i + 1);

		if (sender != "F") {
			if (sender == prevSender) {
				++excitement;
				continue;
			}
		}
		else {  //sender == "F"
			if (prevSender != "F") {
				if (prevSender == nextSender) {
					// 2 or nothing.
				}
				else{
					// 1 for sure
					++excitement;
				}
			}
			else {
				// 0 or nothing
			}
		}

	}


	return 0;
}





