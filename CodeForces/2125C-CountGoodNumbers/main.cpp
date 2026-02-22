#include <iostream>
#include <vector>
#include <cmath>

typedef  unsigned long long ull;
using namespace std;

int main() {
    int T;
    cin >> T;

    // Claim: x is a good number iff x + 2 * 3 * 5 * 7 is also a good number.
    int K = 2 * 3 * 5 * 7;
    vector<bool> good_le_k (K + 1, false);

    // Compute all the good numbers <= k.
    for (int i = 1; i <= K; ++i) {
        // Check if i is a good number
        if (i % 2 != 0 && i % 3 != 0 && i % 5 != 0 && i % 7 != 0) {
            good_le_k[i] = true;
        }
    }

    vector<ull> pref(K + 1, 0);
    pref[0] = 0;  
    for (int i = 1; i <= K; ++i) {
        pref[i] = pref[i - 1] + (good_le_k[i] ? 1 : 0);
    }

    while (T--) {
        ull l, r, count_l = 0, count_r = 0;
        cin >> l >> r;

        if (r > K) {
            for (int i = 1; i <= K; ++i) {
                if (!good_le_k[i]) continue;
                ull x = (ull) i;
                count_r += (r - x) / K + 1;
            }
        } else {
            count_r = pref[r];
        }

        if (l - 1 > K) {
            for (int i = 1; i <= K; ++i) {
                if (!good_le_k[i]) continue;
                ull x = (ull) i;
                count_l += ((l - 1) - x) / K + 1;
            }
        } else {
            count_l = pref[l - 1];
        }
    
        
        cout << count_r - count_l << endl;
    }
        

    return 0;
}