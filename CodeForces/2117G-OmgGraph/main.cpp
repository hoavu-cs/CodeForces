#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

constexpr int INF = 2e9 + 100;

// Union-Find (Disjoint Set Union) data structure of integers

struct Edge {
    int u, v, weight;
};


class UnionFind {

private:
    vector<int> parent;
    vector<int> rank;

public:

    // Initialize the Union-Find structure with n elements
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    // Find the root of the set containing x
    int find(int x) {
        while (x != parent[x]) {
            x = parent[x];
        }
        return x;
    }

    // Union the sets containing x and y
    void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                parent[root_x] = root_y;
            } else if (rank[root_x] > rank[root_y]) {
                parent[root_y] = root_x;
            } else {
                parent[root_y] = root_x;
                rank[root_x]++;
            }
        }
    }
};

// Perform BFS on a tree to find the lightest heaviest edge path from source to all nodes
void tree_dfs_heaviest_edge(int node, int parent, const vector<vector<Edge>> &adj, vector<int> &heaviest) {
    for (const auto &edge : adj[node]) {
        if (edge.v != parent) {
            heaviest[edge.v] = max(edge.weight, heaviest[node]);
            tree_dfs_heaviest_edge(edge.v, node, adj, heaviest);
        }
    }
}

int main() {
    int T;
    cin >> T;

    /*
        Idea:
        Consider a minimum spaning tree (MST) of the graph.
        Claim: the path between u and v minimizes the maximum edge weight on the path.
        Proof sketch: Let P be the path from u to v in the MST. Suppose there is another path P' from u to v with a lighter heaviest edge. 
        Exchanging the two heaviest edge in P and P' would not increase the weight of the MST.

        Thus, the optimal path from 1 to n must go through some edge uv where uv is the minimum edge weight in the path.
        If we know uv, we need to find the paths with lightest heaviest edge weight from 1 to u and from v to n. These paths are known from the MST.
        Thus, we can try different uv and return the best path.

        Edge case: u=1, v=n, then the path is just uv and the answer is 2 * w.
    */

    while (T--) {
        int n, m, ans = INF;
        cin >> n >> m;
        vector<Edge> edges; // (u, v, weight)
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }

        sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
            return a.weight < b.weight;
        });

        UnionFind uf(n);

        // Compute the MST
        vector<vector<Edge>> mst_edges(n + 1);
        int total_weight = 0;
        for (const auto &e : edges) {
            int u = e.u;
            int v = e.v;
            int w = e.weight;

            if (uf.find(u) != uf.find(v)) {
                uf.union_sets(u, v);
                mst_edges[u].push_back({u, v, w});
                mst_edges[v].push_back({v, u, w});
                total_weight += w;
            }
        }


        // Compute heaviest edge on path from 1 and n to others in the MST
        vector<int> heaviest_from_1(n + 1, -INF);
        heaviest_from_1[1] = 0;  
        tree_dfs_heaviest_edge(1, -1, mst_edges, heaviest_from_1);
        vector<int> heaviest_from_n(n + 1, -INF);
        heaviest_from_n[n] = 0;
        tree_dfs_heaviest_edge(n, -1, mst_edges, heaviest_from_n);

        for (const auto &e : edges) {
            int u = e.u;
            int v = e.v;
            int w = e.weight;

            if ((u == 1 && v == n) || (u == n && v == 1)) {
                ans = min(ans, 2 * w);
            } else {
                ans = min(ans, w + max(heaviest_from_1[u], heaviest_from_n[v]));
                ans = min(ans, w + max(heaviest_from_1[v], heaviest_from_n[u]));
            }  
        }

        cout << ans << endl;
    }

    return 0;
}