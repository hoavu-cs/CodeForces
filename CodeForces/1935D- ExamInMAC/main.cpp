#include <iostream>
#include <vector>

using namespace std;

long count_sum(long x) {
    // return the number of pairs (a, b) such that a + b = x 
    // 0 <= a <= b
    if (x % 2 == 0) {
        return x / 2 + 1;
    } else {
        return (x + 1) / 2;
    }
}

long count_diff(long x, long c) {
    // return the number of pairs (a, b) such that b - a = x
    // 0 <= a <= b <= c
    return c - x + 1;
}

int main() {
    int num_tests;
    cin >> num_tests;

    while (num_tests-- > 0) {
        long long n, c;
        cin >> n >> c;
        vector<long> s(n);
        long long num_pairs = (c + 1) * c / 2 + c + 1;
        long long complement_sz = 0, ans = 0, even = 0, odd = 0;

        for (int i = 0; i < n; i++) {
            cin >> s[i];
            complement_sz += count_sum(s[i]) + count_diff(s[i], c);
            if (s[i] % 2 == 0) {
                even++;
            } else {
                odd++;
            }
        }

        complement_sz -= even * (even - 1) / 2 + odd * (odd - 1) / 2 + n;
        ans = num_pairs - complement_sz;
        cout << ans << endl;
    }

    return 0;
}
