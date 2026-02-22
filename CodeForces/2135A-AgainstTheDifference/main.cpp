#include <iostream>
#include <vector>
#include <map>

using namespace std;

int binary_search(const vector<int>& v, int target) {
    int left = 0, right = v.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            return mid;
        } else if (v[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        map<int, vector<int>> p;
        
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            p[a[i]].push_back(i);
        }  

        vector<int> dp(n, 0);
        dp[0] = (a[0] == 1) ? 1 : 0;
        /*
            dp[i] = length of the longest neat subsequence in a[0..i]
            the best subsequence either contains a[i] or it doesn't
            1. if it doesn't contain a[i], dp[i] = dp[i-1]
            2. if it contains a[i], let x = a[i]
            we need to find index j where the current x-block begins
            dp[i] = max(dp[i], dp[j-1] + x).
            Note that j = p[x][i - x + 1].
        */
        for (int i = 1; i < n; ++i) {

            dp[i] = dp[i-1];
            int x = a[i];
            int j = binary_search(p[x], i);
            if (j >= a[i] - 1) { // ensure that we have enough elements for an x-block
                int prev_idx = p[x][j - x + 1];
                if (prev_idx == 0) {
                    dp[i] = max(dp[i], x);
                } else {
                    dp[i] = max(dp[i], dp[prev_idx - 1] + x);
                }
            }
        }
        cout << dp[n-1] << endl;
    }

    return 0;
}