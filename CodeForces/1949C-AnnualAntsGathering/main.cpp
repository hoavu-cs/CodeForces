#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>

using namespace std;
const int N = 2e5 + 1;
vector<int> sz (N);
vector<list<int>> edges (N);

void dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : edges[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

int centroid(int u, int p, int n) {
    for (auto v : edges[u]) {
        if (sz[v] > static_cast<double>(n)/2 && v != p) {
            return centroid(v, u, n);
        }
    }
    return u;
}

bool gather(int u, int p) {
    // return true if the tree rooted at u can be gathered at u
    vector<int> children_sz, accumulated_children_sz;
    sz[u] = 1;
    for (auto v : edges[u]) {
        if (v != p) {
            if (!gather(v, u)) {
                // if any subtree cannot be gathered, return false
                return false;
            }
            children_sz.push_back(sz[v]);
            sz[u] += sz[v];
        }
    }

    sort(children_sz.begin(), children_sz.end());
    accumulated_children_sz.push_back(1);
    
    for (int i = 0; i < children_sz.size(); i++) {
        accumulated_children_sz.push_back(accumulated_children_sz[i] + children_sz[i]);
        if (accumulated_children_sz[i] < children_sz[i]) {
            // if the accumulated children subtree size is less than the next child subtree size, return false
            return false;
        }
    }
    return true;
}

int main() {
    int n; // tree size
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    dfs(1, 0);
    int centroid_id = centroid(1, 0, n);
    fill(sz.begin(), sz.end(), 0);
    bool result = gather(centroid_id, 0);
    
    if (result) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}