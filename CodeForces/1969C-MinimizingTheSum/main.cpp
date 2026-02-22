#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num_tests;
    cin >> num_tests;

    while (num_tests--) {
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // dp[i][j] = min sum of subarray a[0..i] with j steps
        vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));

        // base cases
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            dp[i][0] = sum;
        }

        for (int j = 1; j <= k; j++) {
            dp[0][j] = a[0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j] = dp[i - 1][j] + a[i];
                long long x = 0, y = 0;

                for (int l = 1; l <= j; l++) {
                    if (i - l < 0) {
                        break;
                    } else {
                        // spread a[i] backward
                        x = a[i] * (l + 1);
                        if (i - l - 1 >= 0) {
                            dp[i][j] = min(dp[i][j], dp[i - l - 1][j - l] + x);
                        } else {
                            dp[i][j] = min(dp[i][j], x);
                        }

                        // spread a[l] forward
                        y = a[i - l] * l;
                        if (i - l >= 0) {
                            dp[i][j] = min(dp[i][j], dp[i - l][j - l] + y);
                        } else {
                            dp[i][j] = min(dp[i][j], y);
                        }

                    }
                }
            }
        }

        cout << dp[n - 1][k] << endl;
    }
    return 0;
}