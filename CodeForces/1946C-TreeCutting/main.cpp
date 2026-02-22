#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <cmath>

using namespace std;

int N, x, k, n_count = 0, k_count = 0;
vector<vector<int>> edges;
vector<int> tree_size;
vector<bool> visited;

void dfs(int node) {
    visited[node] = true;
    tree_size[node] = 1;

    for (auto &v : edges[node]) {
        if (!visited[v]) {
            dfs(v);
            tree_size[node] += tree_size[v];
        }
    }

    if (tree_size[node] >= x && k_count <= k - 1) {
        n_count += tree_size[node];
        k_count++;
        tree_size[node] = 0;
    } else if (tree_size[node] >= x && k_count == k && node == 1) {
        n_count += tree_size[node];
        k_count++;
        tree_size[node] = 0;
    }
}

int main() {
    int n_tests;
    cin >> n_tests;
    N = pow(10, 5) + 1;

    while (n_tests > 0) {

        int n = 0;
        cin >> n >> k;
        edges.assign(n + 1, vector<int>());

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        int left = 1, right = n, ans = 0;
        
        while (left <= right) {
            x = (left + right)/2;

            // reset global variables for dfs
            tree_size.assign(n + 1, 0); 
            visited.assign(n + 1, false);
            n_count = 0, k_count = 0;

            dfs(1);

            if (k_count - 1 == k && n_count >= n) {
                ans = x;
                left = x + 1;
            } else {
                right = x - 1;
            }
        }

        cout << ans << endl;
        n_tests--;
    }

    return 0;
}