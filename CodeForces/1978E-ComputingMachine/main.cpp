#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    int num_tests;
    cin >> num_tests;

    while (num_tests--) {
        int n, num_queries;
        string s, t, s_copy, t_copy;

        cin >> n >> s >> t >> num_queries;
        s_copy = s;
        t_copy = t;

        vector<int> dp (n, 0);

        for (int i = 1; i < n - 1; i++) {
            if (s[i - 1] == '0' && s[i + 1] == '0') {
                t[i] = '1';
            }
        }

        dp[0] = (s[0] == '1');

        for (int i = 1; i < n - 1; i++) {
            if (t[i - 1] == '1' && t[i + 1] == '1') 
                s[i] = '1';

            dp[i] = dp[i - 1] + (s[i] == '1');
        }

        dp[n - 1] = dp[n - 2] + (s[n - 1] == '1');

        while (num_queries--) {
            int l, r, ans;
            cin >> l >> r;

            if (r - l == 0) {
                ans = (s_copy[l - 1] == '1');
            } else if (r - l == 1) {
                ans = (s_copy[l - 1] == '1') + (s_copy[r - 1] == '1');
            } else if (r - l == 2) {
                ans = (s_copy[l - 1] == '1') + (s_copy[r - 1] == '1');
                ans += (t_copy[l - 1] == '1' && t_copy[l + 1] == '1') || (s_copy[l] == '1');
            } else if (l == 1) {
                ans = dp[r - 1];

                // check if the original rightmost element is 0
                if (s[r - 1] == '1' && s_copy[r - 1] == '0') 
                    ans--;

                // check if the original second rightmost element is 0
                if (s[r - 2] == '1' && s_copy[r - 2] == '0' && t_copy[r - 1] == '0' && (r - l > 1))
                    ans--;
            } else {
                ans = dp[r - 1] - dp[l - 2];

                // check if the original leftmost element is 0
                if (s_copy[l - 1] == '0' && s[l - 1] == '1') 
                    ans--;
                    
                // check if the original rightmost element is 0
                if (s_copy[r - 1] == '0' && s[r - 1] == '1')  
                    ans--;

                // check if the second rightmost element is 0
                if (s[r - 2] == '1' && s_copy[r - 2] == '0' && t_copy[r - 1] == '0')
                    ans--;

                // check if the second leftmost element is 0
                if (s[l] == '1' && s_copy[l] == '0' && t_copy[l - 1] == '0')
                    ans--;
            }
            cout << ans << endl;
        }
    }

    return 0;
}