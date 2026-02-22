#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(vector<map<int, int>>& graph1,
                vector<map<int, int>>& graph2,
                vector<int>& dist, 
                vector<int>& prev, 
                int start, int L1, int L2) {

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (pq.size() > 0) {
        int d = pq.top().first;
        int u = pq.top().second;

        pq.pop();
        
        if (d > dist[u]) continue;

        for (auto& edge : graph1[u]) {
            int v = edge.first;
            int w1 = edge.second;
            int w2 = graph2[u][v];

            if (dist[u] + w1 <= L1 && dist[v] > dist[u] + w1) {
                dist[v] = dist[u] + w1;
                prev[v] = u;
                pq.push({dist[v], v});
            } else {
                if (dist[u] >= L2) {
                    if (dist[v] > dist[u] + w1) {
                        dist[v] = dist[u] + w1;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                } else {
                    int x = dist[u] + w2;
                    int y = w1 + L2;
                    int z = min(x, y);

                    if (dist[v] > z) {
                        dist[v] = z;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }   
                }
            }

            
        }
    } 
}

int main() {

    int num_tests;
    cin >> num_tests;
    
    while (num_tests--) {
        int n, m, t0, t1, t2, ans;
        cin >> n >> m >> t0 >> t1 >> t2;

        vector<map<int, int>> graph1(n + 1);
        vector<map<int, int>> graph2(n + 1);

        for (int i = 0; i < m; i++) {
            int u, v, w1, w2;
            cin >> u >> v >> w1 >> w2;
            graph1[u][v] = w1;   
            graph2[u][v] = w2;
            graph1[v][u] = w1;
            graph2[v][u] = w2;
        }

        vector<int> dist(n + 1, 1e9);
        vector<int> prev(n + 1, -1);
        
        int L1 = t0 - t2,  L2 = t0 - t1;

        dijkstra(graph1, graph2, dist, prev, n, L1, L2);
        ans = max(-1, t0 - dist[1]);
        cout << ans << endl;
    }

    return 0;

}