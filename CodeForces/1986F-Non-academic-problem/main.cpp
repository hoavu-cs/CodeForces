#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const long long MAXN = 2 * 1e5 + 10;
long long n, m, currentTime, ans;
vector<vector<long long>> adj;
vector<long long>  parent, pre, post, top, sz;
vector<bool> visited;
set<pair<long long, long long>> non_bridges;

void dfs(long long u, long long p) {
    visited[u] = true;
    parent[u] = p;
    pre[u] = currentTime++;

    // y stores the ancestor of u that is visited first in the DFS traversal
    // all edges from u to y in the DFS trees can be deleted without disconnecting the graph
    long long y = 0; 

    for (long long v : adj[u]) {
        if (v == p) continue;

        if (visited[v]) {
            non_bridges.insert(make_pair(min(u, v), max(u, v)));
            if (pre[v] < pre[top[u]]) {
                top[u] = v;
            }
        } else {
            dfs(v, u);
            if (pre[top[v]] < pre[top[u]]) {
                top[u] = top[v];
            }
        }
    }
    post[u] = currentTime++;
}

bool compare_by_second(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    return a.second < b.second;
}

void make_non_bridges() {
    vector<pair<long long, long long>> pre_order = vector<pair<long long, long long>>(n + 1);

    for (long long i = 1; i <= n; i++) {
        pre_order[i] = {i, pre[i]};
    }

    sort(pre_order.begin() + 1, pre_order.end(), compare_by_second);

    for (long long i = 1; i <= n; i++) {
        long long u = pre_order[i].first;
        long long it = u;

        while (it != top[u]) {
            pair<long long, long long> edge = make_pair(min(it, parent[it]), max(it, parent[it]));

            if (non_bridges.find(edge) == non_bridges.end()) {
                non_bridges.insert(edge);
                it = parent[it];
            } else {
                break;
            }
        }
    }
}

void dfs2(long long u) {
    visited[u] = true;
    sz[u] = 1;
    for (long long v : adj[u]) {
        if (!visited[v]) {
            dfs2(v);
            sz[u] += sz[v];

            if (non_bridges.find(make_pair(min(u, v), max(u, v))) == non_bridges.end()) {
                long long u_part = n - sz[v], v_part = sz[v];
                ans = min(ans, u_part * (u_part - 1) / 2 + v_part * (v_part - 1) / 2);
            }
        }
    }
}

int main() {
    long long num_tests;
    cin >> num_tests;

    while (num_tests--) {
        cin >> n >> m;

        // initialize the vectors
        adj = vector<vector<long long>>(n + 1);
        parent = vector<long long>(n + 1);
        pre = vector<long long>(n + 1);
        post = vector<long long>(n + 1);
        top = vector<long long>(n + 1);
        sz = vector<long long>(n + 1, 0);
        visited = vector<bool>(n + 1, false);
        non_bridges.clear();
        currentTime = 1;
        pre[0] = MAXN;
        ans = n * (n - 1) / 2;

        for (long long i = 1; i <= n; i++) {
            top[i] = i;
        }

        // read in the graph
        for (long long i = 0; i < m; i++) {
            long long u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // run the DFS
        dfs(1, 0);

        // find the non-bridges
        make_non_bridges();

        // run the DFS again
        visited = vector<bool>(n + 1, false);
        dfs2(1); 

        cout << ans << endl;
    }
    return 0;
}