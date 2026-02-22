#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    long long num_tests = 0;
    cin >> num_tests;
    
    while (num_tests--) {
        long long n = 0, m = 0;
        cin >> n >> m;
        
        vector<long long> a(n + m + 1, 0), b(n + m +1, 0), prefix_sum_a(n + m + 1, 0), prefix_sum_b(n + m + 1, 0);

        for (int i = 0; i < n + m + 1; i++) {
            cin >> a[i];
            if (i == 0) {
                prefix_sum_a[i] = a[i];
            } else {
                prefix_sum_a[i] = prefix_sum_a[i - 1] + a[i];
            }
        }

        for (int i = 0; i < n + m + 1; i++) {
            cin >> b[i];
            if (i == 0) {
                prefix_sum_b[i] = b[i];
            } else {
                prefix_sum_b[i] = prefix_sum_b[i - 1] + b[i];
            }
        }

        vector<long long> total_skill(n + m + 1, 0), total_skill_2(n + m + 1, 0);
        vector<long long> ans(n + m + 1, 0);
        long long pa = -1, pb = -1, num_programmers = 0, num_testers = 0, skill_so_far = 0;

        for (int i = 0; i < n + m + 1; i++) {
            if (a[i] > b[i]) {
                num_programmers++;
                skill_so_far += a[i];
            } else {
                num_testers++;
                skill_so_far += b[i];
            }
            total_skill[i] = skill_so_far;

            if (num_programmers == n + 1 && pa == -1) {
                pa = i;
            } 

            if (num_testers == m + 1 && pb == -1) {
                pb = i;
            }
        }
  
        num_programmers = 0, num_testers = 0, skill_so_far = 0;
        for (int i = 0; i < n + m + 1; i++) {
            if (num_programmers == n) {
                skill_so_far += b[i];
                num_testers++;
            } else if (num_testers == m) {
                skill_so_far += a[i];
                num_programmers++;
            } else {
                if (a[i] > b[i]) {
                    num_programmers++;
                    skill_so_far += a[i];
                } else {
                    num_testers++;
                    skill_so_far += b[i];
                }
            }
            total_skill_2[i] = skill_so_far;
        }

        for (int i = 0; i < n + m + 1; i++) {
            if (a[i] > b[i]) {
                if (pa == - 1) {
                    if (pb > 0) {
                        ans[i] = total_skill[pb - 1] + prefix_sum_a[n + m] - prefix_sum_a[pb - 1] - a[i];
                    } else {
                        ans[i] = prefix_sum_a[n + m] - a[i];
                    }
                } else {
                    if (i >= pa) {
                        if (i - 1 >= 0) {
                            ans[i] = total_skill_2[i - 1] + prefix_sum_b[n + m] - prefix_sum_b[i - 1] - b[i];
                        } else {
                            ans[i] = prefix_sum_b[n + m] - b[i];
                        }
                        
                    } else {
                        ans[i] = total_skill[pa] - a[i] + prefix_sum_b[n + m] - prefix_sum_b[pa];
                    }

                }
            } else {
                if (pb == -1) {
                    if (pa > 0) {
                        ans[i] = total_skill[pa - 1] + prefix_sum_b[n + m] - prefix_sum_b[pa - 1] - b[i];
                    } else {
                        ans[i] = prefix_sum_b[n + m] - b[i];
                    }
                } else {
                    if (i >= pb) {
                        if (i - 1 >= 0) {
                            ans[i] = total_skill_2[i - 1] + prefix_sum_a[n + m] - prefix_sum_a[i - 1] - a[i];
                        } else {
                            ans[i] = prefix_sum_a[n + m] - a[i];
                        }
                    } else {
                        ans[i] = total_skill[pb] - b[i] + prefix_sum_a[n + m] - prefix_sum_a[pb];
                    }
                }
            }
        }
        
        for (int i = 0; i < n + m + 1; i++) {
            cout << ans[i] << " ";
        }

        cout << endl;
    }

    return 0;
}