#include <iostream>
#include <cmath>

using namespace std;



int main() {
	long int size;
	cin >> size;


	long long int output = 1;
	for (long int i = 1; i < size; ++i) {
		output *=  2;
		cout << "h";
	}
	cout << output;

	//cout << (int)fmod(exp2(size - 1), 998244353);
	cout << (int)fmod(output, 998244353);

	return 0;
}