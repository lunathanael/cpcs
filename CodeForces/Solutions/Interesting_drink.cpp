#include <iostream>
#include <algorithm>

using namespace std;

int start;

long long int minn = 1'000'000'001;
long long int maxx = -1;

int main() {
    int shop_number;
    cin >> shop_number;

    start = (shop_number - 1) / 2;

    long long int shop_prices[shop_number];
    for (int i = 0; i < shop_number; ++i) {
        long long int price; cin >> price;
        shop_prices[i] = price;
    }

    sort(shop_prices, shop_prices + shop_number);

    int days;
    cin >> days;

    while (days--) {
        long long int money;
        cin >> money;

        int L = -1;
        int H = shop_number;
        int target = start;
        int can;

        while ((L + 1) != H) {
            if (money >= shop_prices[target]) {
                L = target;
            }
            else {
                H = target;
            }
            target = (H + L) / 2;
        }

        cout << L + 1 << endl;
    }

    return 0;
}