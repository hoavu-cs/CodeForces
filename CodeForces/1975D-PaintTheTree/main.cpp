#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int N = 2e5 + 1;
vector<int> depth (N);
vector<int> path;
vector<list<int>> edges (N);

void dfs_depth(int u, int p) {
    for (auto v : edges[u]) {
        if (v != p) {
            dfs_depth(v, u);
            depth[u] = max(depth[u], depth[v] + 1);
        }
    }
}

bool dfs_path(int u, int p, int b) {
    
    if (u == b) {
        path.push_back(u);
        return true;
    }

    for (auto v : edges[u]) {
        if (v != p) {
            bool contain_b = dfs_path(v, u, b);
            if (contain_b) {
                path.push_back(u);
                return true;
            }
        }
    }
    return false;
}
    
int main() {
    int num_tests;
    cin >> num_tests;
    
    while (num_tests-- > 0) {
        int n, a, b;
        cin >> n >> a >> b;

        depth.assign(n + 1, 0);
        path.clear();
        edges.assign(n + 1, list<int>());

        // read the tree edges
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        dfs_path(a, -1, b);
        int path_length = path.size() - 1;
        int root = path[path.size() / 2];
        dfs_depth(root, -1);
        
        cout << 2 * (n - 1) - depth[root] + path_length / 2 + path_length % 2 << endl;
    }
    return 0;
}