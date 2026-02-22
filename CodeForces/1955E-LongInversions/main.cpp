#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int num_tests;
    cin >> num_tests;
    
    while (num_tests--) {
        int n;
        string s;
        cin >> n;
        cin >> s;
        

        for (int k = n; k >= 1; k--) {
            vector<int> difference (n + 1, 0);
            int num_inversions = 0;

            if (s[0] == '1') {
                difference[0] = 0;
            } else {
                difference[0] = 1;
                difference[k] = -1;
                num_inversions = 1;
            }

            for (int i = 1; i <= n - k; i++) {
                num_inversions += difference[i];
                if ((s[i] == '1') && (num_inversions % 2 == 1)) {
                    difference[i] += 1;
                    difference[i + k] -= 1;
                    num_inversions += 1;
                } else if ((s[i] == '0') && (num_inversions % 2 == 0)) {
                    difference[i] += 1;
                    difference[i + k] -= 1;
                    num_inversions += 1;
                }
            }

            bool flag = true;
            num_inversions = 0;

            for (int i = 0; i < n; i++) {
                num_inversions += difference[i];
                if ((s[i] == '1') && (num_inversions % 2 == 1)) {
                    flag = false;
                } else if ((s[i] == '0') && (num_inversions % 2 == 0)) {
                    flag = false;
                }       
            }

            if (flag) {
                cout << k << endl;
                break;
            }
        }
    }

    return 0;
}