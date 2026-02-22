#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int search(vector<int> &a, int j) {
    // find the smallest i such that a[i] + a[i + 1] > a[j] 
    int l = 0, r = j, ans = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] + a[m + 1] > a[j]) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return ans;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        sort(a.begin(), a.end());
        int ans = n;

        for (int j = n - 1; j >= 2; j--) {
            // for each a[j] find the smallest i such that a[i] + a[i + 1] > a[j]
            // try setting a[0...i-1] to a[i] and a[j+1...n-1] to a[j] 
            // return the best answer over all j
            int i = search(a, j);
            ans = min(ans, n - j - 1 + i);
        }

        cout << ans << endl;
    }
    
    return 0;
}