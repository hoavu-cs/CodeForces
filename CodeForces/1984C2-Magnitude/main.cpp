#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
typedef long long ll;
const int mod =  998244353;

int main() {
    int num_tests;
    cin >> num_tests;

    while (num_tests--) {
        int n; 
        cin >> n;

        vector<ll> a(n);
        vector<ll> large(n), small(n), large_count(n), small_count(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        large[0] = a[0];
        small[0] = a[0];
        small_count[0] = 1;
        ll sum = 0;
        
        int i = 0;
        while (i < n && sum + a[i] >= 0) {
            if (i == 0) {
                large[i] = a[i];
                small[i] = a[i];
                large_count[i] = 2;
                small_count[i] = 0;
            } else {
                large[i] = a[i] + large[i - 1];
                small[i] = a[i] + small[i - 1];
                large_count[i] = large_count[i-1] * 2 % mod;
                small_count[i] = 0;
            }
            sum += a[i];
            i++;
        }

        if (i == 0) {
            large[i] = abs(a[i]);
            small[i] = a[i];
            large_count[i] = 1;
            small_count[i] = 1;
            i++;
        }

        while (i < n) {
            ll x = a[i] + large[i - 1], y = abs(a[i] + large[i - 1]), z = a[i] + small[i - 1], w = abs(a[i] + small[i - 1]);

            large[i] = max(x, max(y, max(z, w)));
            large_count[i] = (int(large[i] == x) + int(large[i] == y)) * large_count[i - 1] % mod;
            large_count[i] = (large_count[i] + (int(large[i] == z) + int(large[i] == w)) * small_count[i - 1]) % mod;

            small[i] = min(x, min(y, min(z, w)));
            small_count[i] = (int(small[i] == x) + int(small[i] == y)) * large_count[i - 1] % mod;
            small_count[i] = (small_count[i] + (int(small[i] == z) + int(small[i] == w)) * small_count[i - 1]) % mod;

            i++;
        }

        cout << large_count[n - 1] % mod << endl;
    }

    return 0;
}