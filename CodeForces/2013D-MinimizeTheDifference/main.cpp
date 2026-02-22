#include <iostream>
#include <vector>
#include <climits>

using namespace std;
typedef long long ll;

int main() {
    int num_tests;
    cin >> num_tests;

    while (num_tests--) {
        // reading the next test case
        int n;
        cin >> n;

        vector<ll> a(n);
        vector<pair<ll, ll>> s; 

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // This is where the algorithm starts. 
        s.push_back({a[0], 1});

        for (int i = 1; i < n; i++) {
            if (a[i] == s.back().first) {
                s.back().second++;
            } else if (a[i] > s.back().first) {
                s.push_back({a[i], 1});
            } else {
                ll sum = a[i];
                int num_elements = 1;
                
                // Simulate stack pop and aggregate elements
                while (!s.empty() && sum / num_elements < s.back().first) {
                    sum += s.back().first * s.back().second;
                    num_elements += s.back().second;
                    s.pop_back(); // pop from vector
                }

                ll d = sum / num_elements;
                ll r = sum % num_elements;

                s.push_back({d, num_elements - r});
                if (r) s.push_back({d + 1, r});
            }
        }
        // Output the difference between the largest and smallest elements. This is where I replace the loop in my video.
        cout << s.back().first - s.front().first << endl;
    }

    return 0;
}