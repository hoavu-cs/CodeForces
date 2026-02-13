#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

constexpr int INF = 1e9 + 5;

struct Point {
    int x, y;
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, Ax, Ay, Bx, By, max_x = -INF, min_x = INF;
        cin >> n >> Ax >> Ay >> Bx >> By;
        vector<Point> points (n, {0, 0});
        map<int, int> top, bottom;
        set<int> x_coordinates_set;

        for (int i = 0; i < n; ++i) {
            cin >> points[i].x;
            top[points[i].x] = -INF;
            bottom[points[i].x] = INF;
            x_coordinates_set.insert(points[i].x);
        }

        max_x = *x_coordinates_set.rbegin();
        min_x = *x_coordinates_set.begin();

        for (int i = 0; i < n; ++i) {
            cin >> points[i].y;
        }
        
        for (const auto& point : points) {
            // Maintain top and bottom y-coordinates for each x-coordinate
            top[point.x] = max(top[point.x], point.y);
            bottom[point.x] = min(bottom[point.x], point.y);
        }

        vector<int> x_coordinates (x_coordinates_set.begin(), x_coordinates_set.end());
        int m = x_coordinates.size();
        vector<ll> dp_top (m, INF), dp_bottom (m, INF);

        for (int i = m - 1; i >= 0; --i) {
            int x = x_coordinates[i];
            ll sweep_cost = top[x] - bottom[x]; 
            if (i == m - 1) {   
                dp_top[i] = sweep_cost + abs(Bx - x) + abs(By - bottom[x]);
                dp_bottom[i] = sweep_cost + abs(Bx - x) + abs(By - top[x]);
            } else {
                int next_x = x_coordinates[i + 1];
                // fill out dp bottom
                // current bottom -> current top -> next top 
                ll bottom_to_top = sweep_cost + (next_x - x) + abs(top[next_x] - top[x]) + dp_top[i + 1];
                // current bottom -> current top -> next bottom 
                ll bottom_to_bottom = sweep_cost + (next_x - x) + abs(bottom[next_x] - top[x]) + dp_bottom[i + 1];
                dp_bottom[i] = min(bottom_to_bottom, bottom_to_top);
                // fill out dp top
                // current top -> current bottom -> next bottom 
                ll top_to_bottom = sweep_cost + (next_x - x) + abs(bottom[next_x] - bottom[x]) + dp_bottom[i + 1];
                // current top -> current bottom -> next top 
                ll top_to_top = sweep_cost + (next_x - x) + abs(top[next_x] - bottom[x]) + dp_top[i + 1];
                dp_top[i] = min(top_to_bottom, top_to_top);
            }
        }
        ll ans = min(abs(Ax - x_coordinates[0]) + abs(Ay - top[x_coordinates[0]]) + dp_top[0], 
                  abs(Ax - x_coordinates[0]) + abs(Ay - bottom[x_coordinates[0]]) + dp_bottom[0]);

        cout << ans << endl;

    }
    return 0;
}