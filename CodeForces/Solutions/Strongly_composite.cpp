#include <iostream>
#include <math.h>
#include <cstring>

using namespace std;


bool primes[10'000'000] = {};



long long int prime;
long long int doubles;



// A function to print all prime factors of a given number n
void primeFactors(int n)
{
    // Print the number of 2s that divide n
    while (n % 2 == 0) {
        ++prime;
        if (primes[2]) {
            ++doubles;
            primes[2] = false;
        }
        else {
            primes[2] = true;
        }
        n = n / 2;
    }

    double nsqrt = sqrt(n);
    // n must be odd at this point.  So we can skip one element (Note i = i +2)
    for (int i = 3; i <= nsqrt; i = i + 2) {
        // While i divides n, print i and divide n
        while (n % i == 0) {
            ++prime;

            if (primes[i]) {
                ++doubles;
                primes[i] = false;
            }
            else {
                primes[i] = true;
            }
            n = n / i;
        }
    }

    // This condition is to handle the case when n is a prime number
    // greater than 2
    if (n > 2) {
        ++prime;
        if (primes[n]) {
            ++doubles;
            primes[n] = false;
        }
        else {
            primes[n] = true;
        }
    }
}



int main() {
	int testCases;
	cin >> testCases;


	for (int testCase = 0; testCase < testCases; ++testCase) {
        int length;
        cin >> length;

        for (int i = 0; i < length; ++i) {
            int number;
            cin >> number;
            primeFactors(number);
        }

        int size = 0;
        size += doubles;
        prime -= 2 * doubles;
        size += prime / 3;
        cout << size << endl;
        prime = 0;
        doubles = 0;
        memset(primes, false, sizeof(primes));
	}
	return 0;
}