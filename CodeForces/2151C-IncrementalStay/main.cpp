#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ull;

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        vector<ull> a(2 * n + 1);

        for (int i = 1; i <= 2 * n; i++) {
            cin >> a[i];
        }

        /*
            Idea: for each k, the first k numbers are entries & the last k numbers are exits.
            In between, for index i such that i = k (mod 2), then a[i] is an entry, else an exit.
        */

        vector<ull> prefix_sum(2 * n + 1, 0);
        vector<ull> prefix_sum_even(2 * n + 1, 0), prefix_sum_odd(2 * n + 1, 0);


        for (int i = 1; i <= 2 * n; i++) {
            prefix_sum[i] = prefix_sum[i - 1] + a[i];

            if (i % 2 == 0) {
                prefix_sum_even[i] = prefix_sum_even[i - 2] + a[i];
                prefix_sum_odd[i] = prefix_sum_odd[i - 1];
            } else {
                prefix_sum_odd[i] = prefix_sum_odd[i - 2] + a[i];
                prefix_sum_even[i] = prefix_sum_even[i - 1];
            } 
        }

        for (int k = 1; k <= n; k++) {
            ull total_entry = prefix_sum[k];
            ull total_exit = prefix_sum[2 * n] - prefix_sum[2 * n - k];

            if (k % 2 == 0) {
                total_entry += prefix_sum_even[2 * n - k] - prefix_sum_even[k];
                total_exit += prefix_sum_odd[2 * n - k] - prefix_sum_odd[k];
            } else {
                total_entry += prefix_sum_odd[2 * n - k] - prefix_sum_odd[k];
                total_exit += prefix_sum_even[2 * n - k] - prefix_sum_even[k];
            }

            cout << total_exit - total_entry << " "; 
        }

        cout << endl;

    }

    return 0;
}