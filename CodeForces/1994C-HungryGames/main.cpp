#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num_tests;
    cin >> num_tests;

    while (num_tests--) {
        int n, k = 0;
        long long ans = 0;
        cin >> n >> k;
        
        vector<int> a(n), s(n);
        vector<long long> dp(n);

        // read in the toxicities
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // s[i] holds the largest l such that a[i] + a[i+1] + ... + a[i + l - 1] <= k
        int l = n - 1, r = n - 1, total = a[n - 1];

        if (a[n - 1] <= k) {
            s[n - 1] = 1;
        } else {
            s[n - 1] = 0;
        }

        while (l > 0) {
            l--;
            total += a[l];
            while (total > k) {
                total -= a[r];
                r--;
            }
            s[l] = r - l + 1;
        }

        // dp[i] holds the number of pairs with i as the left endpoint such that 
        // the final toxicity is non-zero
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) {
                // base case
                if (a[i] <= k) {
                    dp[i] = 1;
                } else {
                    dp[i] = 0;
                }
            } else {
                dp[i] = s[i];
                if (i + s[i] + 1< n) {
                    dp[i] += dp[i + s[i] + 1];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            ans += dp[i];
        }

        cout << ans << endl;
    }
    return 0;
}