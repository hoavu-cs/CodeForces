#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const long long MOD = 998244353;
vector<vector<long>> adj;
vector<long long> A, B;

void dfs(long u, long p) {
    A[u] = 1;
    B[u] = 0;
    int n_children = 0;
    
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        A[u] = (A[u] * (A[v] + 1)) % MOD;
        B[u] = (B[u] + (A[v] - 1)) % MOD;
        n_children++;
    }

    B[u] = (B[u] + n_children) % MOD;
}

int main() {

    long n_tests;
    cin >> n_tests;

    while(n_tests-- > 0) {
        long n;
        cin >> n;

        adj.assign(n + 1, vector<long>());  
        A.assign(n + 1, 0);
        B.assign(n + 1, 0);

        for (long i = 0; i < n - 1; i++) {
            long u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0);
        long long ans = A[1] + 1;
        for (long i = 1; i <= n; i++) {
            ans = (ans + B[i]) % MOD;
        }
        
        cout << (ans % MOD + MOD) % MOD << endl;
    }

    return 0;
}