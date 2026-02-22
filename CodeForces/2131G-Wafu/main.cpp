#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

constexpr ull MAX_N = 2e5 + 10;
constexpr ull MAX_K = 1e9 + 10;
constexpr ull MOD = 1e9 + 7;

vector<ull> full_score (MAX_N, 0); // full_score[i] stores the maximum score if we start with {i} with unlimited number of operations

/*
    Observation: to make {x} become an empty set through the given operations, we need 2^{x-1} operations.
    Proof sketch: Let T(x) be the number of required operations. We have T(x) = 1 + T(x-1) + T(x-2) + ... + T(1).
    Hence, T(x) - T(x-1) = (1 + T(x-1) + T(x-2) + ... + T(1)) - (1 + T(x-2) + ... + T(1)) = T(x-1).
    Thus, T(x) = 2 T(x-1).

    Since k <= 10^9, the maximum i for which we can get rid of {i} is 2^{i-1} <= 10^9 which implies i <= 30.
*/

inline ull pow2(ull x) {
    return (1ULL << x);
}

inline ull mul_mod(ull a, ull b) {
    return static_cast<unsigned __int128>(a) * b % MOD;
}

// return the score of {x} with at most k operations assuming k < 2^{x-1}
ull partial_score(ull x, ull k) {
    if (k == 0) return 1;

    ull ans = x % MOD;
    k--; // Remove x and add {1,2,...,x-1} takes one operation

    for (int i = 1; i < x; ++i) {
        if (i > 30) {
            ans = mul_mod(ans, partial_score(i, k));
            break;
        }

        if (k >= pow2(i - 1)) {
            // We are curently at {i,i+1,...,x-1} & have enough operations to remove i to obtain {i+1,...,x-1}
            ans = mul_mod(ans, full_score[i]);
            k -= pow2(i - 1);
        } else {
            // We don't have enough operations to remove i, so we must use partial_score
            ans = mul_mod(ans, partial_score(i, k));
            break;
        }
    }

    return ans % MOD;
}

int main() {
    int T;    
    cin >> T;

    // precompute full_score
    full_score[1] = 1;
    vector<ull> pref(MAX_N, 0);
    pref[1] = 1; // pref[i] = full_score[1] * full_score[2] * ... * full_score[i] % MOD
    for (int i = 2; i < MAX_N; ++i) {
        full_score[i] = mul_mod(i, pref[i - 1]);
        pref[i] = mul_mod(pref[i - 1], full_score[i]);
    }

    while (T--) {
        int n;
        ull k, ans = 1;
        cin >> n >> k;
        vector<ull> S(n);

        for (int i = 0; i < n; ++i) {
            cin >> S[i];
        }

        std::sort(S.begin(), S.end());

        for (int i = 0; i < n; ++i) {
            if (S[i] <= 30 && k >= pow2(S[i] - 1)) {
                ans = mul_mod(ans, full_score[S[i]]);
                k -= pow2(S[i] - 1);
            } else {
                ans = mul_mod(ans, partial_score(S[i], k));
                break;
            }
        }

        cout << ans << endl;
    }

    return 0;
}