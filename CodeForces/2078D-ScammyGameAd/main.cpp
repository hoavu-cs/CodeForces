#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long U64;

int main() {
    int T;
    cin >> T;

    int counter = 1;

    while (T--) {
        int n;
        cin >> n;

        vector<string> leftOp(n), rightOp(n);
        vector<int> leftNum(n), rightNum(n);

        // Read in the input
        for (int i = 0; i < n; ++i) {
            cin >> leftOp[i] >> leftNum[i] >> rightOp[i] >> rightNum[i];
        }

        // Let dpLeft[i] be the maximum multiplier that a value that passed through the left i-th
        // gate can get onward. Define dpRight[i] similarly for the right i-th gate.

        vector<U64> dpLeft(n, 1), dpRight(n, 1);

        // Base case: if the last gate is a "+", then the multiplier is 0, otherwise it's the number itself.
        dpLeft[n - 1] = (leftOp[n - 1] == "+") ? 1 : leftNum[n - 1];
        dpRight[n - 1] = (rightOp[n - 1] == "+") ? 1 : rightNum[n - 1];

        // Fill dpLeft and dpRight from the end to the beginning
        for (int i = n - 2; i >= 0; i--) {
            if (leftOp[i] == "+") {
                dpLeft[i] = dpLeft[i + 1];
            } else {
                if (leftNum[i] == 2) {
                    dpLeft[i] = max(2 * dpLeft[i + 1], 
                                    dpLeft[i + 1] + dpRight[i + 1]);
                } else if (leftNum[i] == 3) {
                    dpLeft[i] = max(3 * dpLeft[i + 1], 2 * dpLeft[i + 1] + dpRight[i + 1]);
                    dpLeft[i] = max(dpLeft[i], dpLeft[i + 1] + 2 * dpRight[i + 1]); 
                }
                
            }

            if (rightOp[i] == "+") {
                dpRight[i] = dpRight[i + 1];
            } else {
                if (rightNum[i] == 2) {
                    dpRight[i] = max(2 * dpRight[i + 1], 
                                    dpLeft[i + 1] + dpRight[i + 1]);
                } else if (rightNum[i] == 3) {
                    dpRight[i] = max(3 * dpRight[i + 1], 2 * dpRight[i + 1] + dpLeft[i + 1]);
                    dpRight[i] = max(dpRight[i], dpRight[i + 1] + 2 * dpLeft[i + 1]); 
                }
            }
        }

        // for (int i = 0; i < n; i++) {
        //     cout << dpLeft[i] << " " << dpRight[i] << endl;
        // }

        U64 left = 1, right = 1;
        for (int i = 0; i < n; i++) {
            U64 leftGain = (leftOp[i] == "+") ? leftNum[i] : (leftNum[i] - 1) * left;
            U64 rightGain = (rightOp[i] == "+") ? rightNum[i] : (rightNum[i] - 1) * right;
            U64 gain = leftGain + rightGain;

            if (i == n - 1) {
                left += gain;
            } else {
                if (dpLeft[i + 1] >= dpRight[i + 1]) {
                    left += gain;
                } else {
                    right += gain;
                }
            }
        }
        // if (counter == 5942) {
        //     cout << n << "$";
        //     for(int i = 0; i < n; i++) {
        //         cout << leftOp[i] << leftNum[i] << rightOp[i]<< rightNum[i];
        //     }
        // }
        

        counter++;

        cout << left + right << endl;
    }

    return 0;
}