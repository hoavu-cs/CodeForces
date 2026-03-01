#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        bool is_sorted = std::is_sorted(a.begin(), a.end());
        if (is_sorted) {
            cout << -1 << endl;
            continue;
        }

        auto [min_it, max_it] = std::minmax_element(a.begin(), a.end());
        int min_value = *min_it;
        int max_value = *max_it;

        int left = 1, right = max_value - min_value;
        int k = 1;
        vector<int> sorted_a = a;
        std::sort(sorted_a.begin(), sorted_a.end());

        while (left <= right) {
            int m = (right + left) / 2;
            // Idea: if a_i is in the wrong position and |a_i - min_value| < m and |a_i - max_value| < m, then we cannot swap a_i back to its correct position.
            // If for all a_i,  a_i - min_value >= m or max_value - a_i >= m, then we can swap any pair of elements to sort the array.
            // To swap a_i and a_j, suppose max_value - a_i >= m and max_value - a_j >= m, we can swap them through max_value. 
            // Similarly, if a_i - min_value >= m and a_j - min_value >= m, we can swap them through min_value.
            // If max_value - a_i >= m and a_j - min_value >= m, we can do the following swaps
            // ai, max, min, aj --> max, ai, min, aj --> min, ai, max, aj --> aj, ai, max, min --> aj, max, ai, min --> aj, min, ai, max --> aj, min, max, ai.
            bool feasible = true;
            for (int i = 0; i < n; ++i) {
                if (a[i] != sorted_a[i]) {
                    if (max_value - a[i] < m && a[i] - min_value < m) {
                        feasible = false;
                        break;
                    }
                }
            }
            if (feasible) {
                k = m;
                left = m + 1;
            } else {
                right = m - 1;
            }
        }
        cout << k << endl;
    }
    return 0;
}