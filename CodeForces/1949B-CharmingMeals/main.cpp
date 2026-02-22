#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int RANGE = pow(10, 9) + 1;

int min_diff_with_shift(vector<int> &a, vector<int> &b, int shift) {
    int n = a.size(), min_diff = RANGE;
    for (int i = 0; i < n; i++) {
        min_diff = min(min_diff, abs(a[i] - b[(i + shift) % n]));
    }
    return min_diff;
}

int main() {
    int n_tests = 0;
    cin >> n_tests;
    
    while (n_tests > 0) {
        int n = 0;
        cin >>  n;
        vector<int> a(n), b(n);
        int ans = 0;
    
        for (int& ai : a) cin >> ai;
        for (int& bi : b) cin >> bi;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        for (int shift = 0; shift < n; shift++) 
            ans = max(ans, min_diff_with_shift(a, b, shift));

        cout << ans << endl;
        n_tests--;
    }

    return 0;
}