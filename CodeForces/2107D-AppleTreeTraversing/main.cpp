#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<vector<int>> edges;
vector<int> parent;
vector<int> pi;
unordered_set<int> remaining;
vector<tuple<int, int, int>> apple_paths;

// Compute the parent of each node in the tree after fixing the root at a given node
void root_tree(int u, int p) {
    for (int v : edges[u]) {
        if (v != p && remaining.count(v)) {
            parent[v] = u;
            root_tree(v, u);
        }
    }
}

// Compute the longest path from the root to any leaf node in terms of the number of nodes
// Tiebreak by the node with max index
tuple<int, int> longest_path (int u, int p) {
    int path_length = 1;
    int leaf_index = u;

    for (int v : edges[u]) {
        if (v != p && remaining.count(v)) {
            auto [length, index] = longest_path(v, u);
            if (length + 1 > path_length || (length + 1 == path_length && index > leaf_index)) {
                path_length = length + 1;
                leaf_index = index;
                pi[v] = u;
            }
        }
    }
    return {path_length, leaf_index};
}

int main() {

    int T;
    cin >> T;

    while (T--) {
        int n;
        
        cin >> n;
        edges = vector<vector<int>>(n + 1);
        parent = vector<int>(n + 1, 0);
        pi = vector<int>(n + 1, 0);
        apple_paths.clear();
        remaining.clear();

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        for (int i = 1; i <= n; i++) {
            remaining.insert(i);
        }

        root_tree(1, 0); // pick a node in the remaining forest

        while (remaining.size() > 0) {
            int root = *remaining.begin(); // pick an arbitrary root from remaining nodes
            // find the leaf u with longest path from root 
            // find the leaf v with longest path from u
            // u and v are the endpoints of the longest path in this tree
            
            auto [length_1, u] = longest_path(root, 0); 
            pi.clear();
            pi[u] = 0; 
            auto [length_2, v] = longest_path(u, 0);

            apple_paths.push_back({length_2, max(u, v), min(u, v)});
            
            // delete nodes along the path from u to v
            while (v != 0) {
                remaining.erase(v);
                v = pi[v];
            }
        }

        sort(apple_paths.begin(), apple_paths.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            if (get<0>(a) != get<0>(b)) {
                return get<0>(a) > get<0>(b); // sort by length descending
            } else {
                if (get<1>(a) != get<1>(b)) {
                    return get<1>(a) > get<1>(b); // sort by max index descending
                } else {
                    return get<2>(a) < get<2>(b); // sort by min index ascending
                }
            }
        });

        for (const auto& [length, max_index, min_index] : apple_paths) {
            cout << length << " " << max_index << " " << min_index << " ";
        }
        cout << endl;
    }

    return 0;
}