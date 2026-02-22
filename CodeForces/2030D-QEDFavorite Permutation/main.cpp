#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int T;
    cin >> T;
    int token_count = 0;

    while (T--) {
        int n, q;
        cin >> n >> q;

        vector<int> p(n + 1), change(q);
        vector<char> s(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> p[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
        }
        for (int i = 0; i < q; i++) {
            cin >> change[i];
        }

        // an index i is bad if s[i] = L and s[i + 1] = R and
        // p[1...i] != {1,2,...,i} since it will block elements
        // claim: the answer is YES if there is no bad index 
        // sketch: if a s[1...i] does not contain L follewed by R, 
        // we can sort elements in p[1...i]

        set<int> bad_index;

        vector<int> max_prefix(n + 1);
        max_prefix[1] = p[1];
        for (int i = 2; i <= n; i++) {
            max_prefix[i] = max(max_prefix[i - 1], p[i]);
        }

        for (int i = 1; i <= n - 1; i++) {
            if (s[i] == 'L' && s[i + 1] == 'R' && max_prefix[i] > i) {
                bad_index.insert(i); // add i to bad index
            }
        }

        for (int i = 0; i < q; i++) {
            int j = change[i];
            if (s[j] == 'L') {
                // if previously, s[j'] = L, it may be bad
                if (bad_index.count(j)) {
                    bad_index.erase(j);
                }
                s[j] = 'R';
                if (s[j - 1] == 'L' && max_prefix[j - 1] > j - 1) {
                    bad_index.insert(j - 1);
                }
            } else {
                s[j] = 'L';
                if (s[j + 1] == 'R' && max_prefix[j] > j) {
                    bad_index.insert(j);
                }
                if (s[j - 1] == 'L' && bad_index.count(j - 1)) {
                    bad_index.erase(j - 1);
                }
            }

            if (bad_index.empty()) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}