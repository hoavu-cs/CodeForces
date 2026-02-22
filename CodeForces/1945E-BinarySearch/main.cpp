#include <iostream>
#include <vector>

using namespace std;

const int INF = 2e5 + 1;

int main() {
    int numTests; 
    cin >> numTests;

    while (numTests-- > 0) {
        int n, x;
        cin >> n >> x;
        vector<int> p(n + 1);
        
        for(size_t i = 1; i <= n; i++) {
            cin >> p[i]; 
        } 

        size_t left = 1, right = n + 1, xIndex = 0, leftMostToX = INF;
        bool onPath = false;

        for (size_t i = 1; i <= n; i++) {
            if (p[i] == x) {
                xIndex = i;
                break;
            }
        }

        while (left < right - 1) {
            int mid = (left + right) / 2;
            
            if (mid == xIndex) {
                onPath = true;
            }

            if (mid > xIndex && mid < leftMostToX) {
                leftMostToX = mid;
            }

            if (p[mid] <= x) {
                left = mid;
            } else {
                right = mid;
            }
        }

        if (!onPath) {
            cout << 1 << endl;
            cout << xIndex << " " << left << endl;
        } else {
            if (p[left] == x) {
                cout << 0 << endl;
            } else if (p[left] < x) {
                cout << 1 << endl;
                cout << xIndex << " " << left << endl;
            } else {
                bool found = false;
                
                for (size_t i = xIndex + 1; i <= leftMostToX; i++) {
                    if (p[i] < x) {
                        cout << 2 << endl; 
                        cout << xIndex << " " << i << endl;
                        cout << i << " " << left << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << 1 << endl;
                    cout << leftMostToX << " " << left << endl;
                }
            }
        }
    }

    return 0; 
}