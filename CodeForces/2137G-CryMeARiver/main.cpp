#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int main() {
    int T;
    cin >> T;
    int test_no = 0;

    while (T--) { 
        int n, m, q;
        cin >> n >> m >> q;
        test_no += 1;

        vector<vector<int>> incoming (n + 1);
        vector<vector<int>> outgoing (n + 1);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            outgoing[u].push_back(v);
            incoming[v].push_back(u);
        }

        vector<bool> dp1(n + 1, false); // dp1[v] = true iff River can win if it is Cry's to play starting at v
        vector<bool> dp2(n + 1, false); // dp2[v] = true iff River can win if it is River's to play starting at v
        vector<bool> is_red(n + 1, false); // is_red[v] = true iff v is colored red
        vector<set<int>> out_dp2 (n + 1);

        /*
            Observe that
            dp1[v] = true iff [v is red] OR ( AND_{edges v->u} [dp2[u] = true])
            dp2[v] = true iff [v is red] OR ( OR_{edges v->u} [dp1[u] = true])
        */
        vector<bool> bfs_visited (n + 1, false);
        
        for (int i = 0; i < q; ++i) {
            int type, v;
            cin >> type >> v;


            if (type == 1) {

                /*
                    Doing a BFS (DFS is fine too) backward to update dp1 and dp2 values
                    1) If dp1[v] is changed to true, then for all u->v, dp2[u] changes to u
                    2) If dp2[v] is changed to true, then increases counter[u] for all u->v by 1
                    If counter[u] = outgoing[u].size(), then dp1[u] changes to true.
                    Note that each edge is processed once so the running time is O(V + E). 
                */ 
                
                queue<int> bfs_queue;
                bfs_queue.push(v);  
                dp1[v] = true;  // Since v is now red, River always win starting at v.
                dp2[v] = true;

                // We do bfs backward to change dp1 and dp2 values. We add v to the queue if we change dp1[v] or dp2[v] from false to true.
                // Then, each edge is processed at most twice.
                while (bfs_queue.size()) {
                    int z = bfs_queue.front();
                    bfs_queue.pop();
                    
                    if (dp1[z]) {
                        for (int w : incoming[z]) {
                            if (!dp2[w]) {
                                dp2[w] = true;
                                bfs_queue.push(w);
                            }
                        }
                    }

                    if (dp2[z]) {
                        for (int w : incoming[z]) {
                            out_dp2[w].insert(z);
                            if (!dp1[w] && out_dp2[w].size() == outgoing[w].size()) {
                                dp1[w] = true;
                                bfs_queue.push(w);
                            }
                        }   
                    }
                }
            } else {
                if (dp1[v]) {
                    cout << "NO" << endl;
                } else {
                    cout << "YES" << endl;
                }
            }
        }

    }

    return 0;
}