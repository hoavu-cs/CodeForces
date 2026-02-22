#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

vector<ll> A; // A[v] = max gold that can be retained in T_v if v is strengthened
vector<ll> B; // B[v] = max gold that can be retained in T_v if v is not strengthened
vector<ll> a; // amount of gold in each camp, 1-index
vector<vector<ll>> adj; // adjacency list, 1-indexed
ll c;

void dfs(ll u, ll p) {
    for (ll v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    A[u] = a[u];
    B[u] = 0;

    for (ll v : adj[u]) {
        if (v == p) continue;
        if (A[v] <= B[v]) { 
            // if it's better not to not strengthen v in T_v, it is obviously not advantageous to strengthen v in T_u
            B[u] += B[v];
            A[u] += B[v] ;
        } else {
            // if it's better to strengthen v in T_v
            B[u] += A[v]; // if don't strengthen u, then it's obvious that we want to strengthen v

            ll x = A[v] - B[v];
            // note that if we strengthen v, it is only advantageous if x > 2 * c since we lose c from each of v and u
            if (x <= 2 * c) {
                A[u] += B[v];
            } else {
                A[u] += A[v] - 2 * c;
            }
        }
    }
}

int main() {
    int num_tests;
    cin >> num_tests;
    
    while (num_tests--) {
        ll n;
        cin >> n >> c;

        a.assign(n + 1, 0);
        adj.assign(n + 1, vector<ll>());
        A.assign(n + 1, 0);
        B.assign(n + 1, 0);

        for (ll i = 1; i <= n; i++) {
            cin >> a[i];
        }

        for (ll i = 0; i < n - 1; i++) {
            ll u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0);
        cout << max(A[1], B[1]) << endl;
    }

    return 0;
}