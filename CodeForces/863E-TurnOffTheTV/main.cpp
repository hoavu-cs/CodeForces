#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

// prototypes

int binary_search_ge(vector<int> &arr, int target);
int binary_search_eq(vector<int> &arr, int target);
vector<vector<int>> build_sparse_table(vector<pair<int, int>> &check_points, vector<int> &starts, vector<int> &ends);
void print_table(vector<vector<int>> &table);
void print_vector(vector<pair<int, int>> &arr);

// functions  

int binary_search_eq(vector<int> &arr, int target) {
    // return the index of the element that is equal to the target, if not found, return -1
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int binary_search_ge(vector<int> &arr, int target) {
    // return the largest index of the element that is less than or equal to the target
    int left = 0, right = arr.size() - 1, ans = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            if (mid > ans) {
                ans = mid;
            }
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
}

vector<vector<int>> build_sparse_table(vector<int> &check_points, vector<int> &starts, vector<int> &ends) {
    int n = check_points.size();
    int num_levels = static_cast<int>(log2(n)) + 1;    
    vector<vector<int>> table(n, vector<int>(num_levels, 0)); 
    
    for (int i = 0; i < n; i++) {
        table[i][0] = binary_search_ge(starts, check_points[i]) - binary_search_ge(ends, check_points[i] - 1);
    }

    for (int level = 1; level < num_levels; level++) {
        for (int i = 0; i < n; i++) {
            int length = (1 << (level - 1));
            if (i + length >= n) {
                break;
            } else {
                table[i][level] = min(table[i][level - 1], table[i + length][level - 1]);
            }
        }
    }

    return table;
}

int get_min_from_table(vector<vector<int>> &table, int left, int right) {
    int length = right - left + 1;
    int level = 0;

    while ((1 << (level + 1)) <= length) {
        level++;
    }

    return min(table[left][level], table[right - (1 << level) + 1][level]);
}
    

int main() {    
    int n;
    cin >> n;

    vector<int> starts(n), ends(n);
    vector<int> check_points, check_points_padded;
    vector<tuple<int, int, int>> time(n);
    
    for (int i = 0; i < n; i++) {
        cin >> starts[i] >> ends[i];
        time[i] = {starts[i], ends[i], i + 1};
        check_points.push_back(starts[i]);
        check_points.push_back(ends[i]);
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    sort(check_points.begin(), check_points.end());

    for (int i = 0; i < check_points.size() - 1; i++) {
        if (check_points[i] == check_points[i + 1] - 1 || check_points[i] == check_points[i + 1]) {
            check_points_padded.push_back(check_points[i]);
        } else {
            check_points_padded.push_back(check_points[i]);
            check_points_padded.push_back(check_points[i] + 1);
        }
    }

    check_points_padded.push_back(check_points[check_points.size() - 1]);
    check_points = check_points_padded;
    vector<vector<int>> table = build_sparse_table(check_points, starts, ends);

    for (int i = 0; i < n; i++) {
        int left_idx = binary_search_eq(check_points, get<0>(time[i]));
        int right_idx = binary_search_eq(check_points, get<1>(time[i]));

        if (get_min_from_table(table, left_idx, right_idx) > 1) {
            cout << get<2>(time[i]) << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}