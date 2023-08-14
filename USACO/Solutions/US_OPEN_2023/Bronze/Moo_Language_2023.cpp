#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// period is max number of sentences
// conjucntion is max number of compound sentences
// transitive is max number of type 2 sentences
// comma is number of type 2 extensions


// first are conjunctions, or maybe last?  (saves periods)
// max number of type 2s, then extending the type 2s
// rest are type 1s




int main() {
	

	int instances;
	cin >> instances;

	while (instances--) {
		int N, C, P; // Words, commas, periods
		cin >> N >> C >> P;
		vector<string> noun;
		vector<string> trans;
		vector<string> intrans;
		vector<string> conj;
		int type_counts[4] = { 0 };

		while (N--) {
			string word;
			cin >> word;
			string word_;
			cin >> word_;
			char a = word_[0];
			if (a == 'n') {
				++type_counts[0];
				noun.push_back(word);
			}
			else if (a == 't') {
				++type_counts[1];
				trans.push_back(word);
			}
			else if (a == 'i') {
				// intrans for type 1
				++type_counts[2];
				intrans.push_back(word);
			}
			else {
				++type_counts[3];
				conj.push_back(word);
			}
		}

		int sentence_count = 0;
		int compound_count = min(P, type_counts[3]);
		int type1 = 0;
		int type2 = 0;
		int type2extra = 0;

		int noun_count = type_counts[0];
		int max_sentence_comp = P + compound_count;
		type1 = min(noun_count, type_counts[2]);
		noun_count = (noun_count - type1) / 2;
		type2 = min(noun_count, type_counts[1]);
		int max_sentence_noun = type1 + type2;
		if (max_sentence_comp > max_sentence_noun) {
			sentence_count = max_sentence_noun;
		}
		else {
			sentence_count = max_sentence_comp;
		}
		if (type2 < sentence_count) {
			type1 = sentence_count - type2;
			int available_nouns = min(type_counts[0] - (type2 * 2) - type1, type_counts[1] - type2);
			type2 += available_nouns;
			type2 = min(sentence_count, type2);
			type1 = sentence_count - type2;
		}
		else {
			type2 = sentence_count;
			type1 = 0;
		}
		if (type2 != 0) {
			type2extra = min(type_counts[0] - (type2 * 2) - type1, C);
		}
		compound_count = min((sentence_count / 2), type_counts[3]);
		int words_used = type2extra + (type1 * 2) + (type2 * 3) + compound_count;
		cout << words_used << "\n";
		// print sentence
		bool compound = false;
		if (type2 > 0 && type2extra != 0) {
			cout << noun[--type_counts[0]] << ' ';
			cout << trans[--type2] << ' ';
			cout << noun[--type_counts[0]];
			while (type2extra--) {
				cout << ", " << noun[--type_counts[0]];
			}
			if (compound_count > 0) {
				--compound_count;
				cout << ' ' << conj[--type_counts[3]];
				compound = true;
			}
			else {
				cout << '.';
			}
			if (type2 != 0 || type1 != 0) {
				cout << ' ';
			}
		}
		while (type2) {
			cout << noun[--type_counts[0]] << ' ';
			cout << trans[--type2] << ' ';
			cout << noun[--type_counts[0]];
			if (compound) {
				compound = false;
				cout << '.';
			}
			else if (compound_count > 0) {
				--compound_count;
				cout << ' ' << conj[--type_counts[3]];
				compound = true;
			}
			else {
				cout << '.';
			}
			if (type2 != 0 || type1 != 0) {
				cout << ' ';
			}
		}
		while (type1) {
			cout << noun[--type_counts[0]] << ' ';
			cout << intrans[--type1];
			if (compound) {
				compound = false;
				cout << '.';
			}
			else if (compound_count > 0) {
				--compound_count;
				cout << ' ' << conj[--type_counts[3]];
				compound = true;
			}
			else {
				cout << '.';
			}
			if (type1 != 0) {
				cout << ' ';
			}
		}
		cout << endl;
	}

	return 0;
}