#include <bits/stdc++.h>
using namespace std;

// TODO: make edges a structure with ids etc.
struct find_bridges { 
    int n;
    vector<vector<int>> adj;
    vector<int> tin, low, edges;
    vector<bool> visited, bridge;

    find_bridges(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, n+1);
        bridge.assign(n, false);
    }

    // ensure u --> v is an edge beforehand
    bool is_bridge(int u, int v) { 
        return low[v] > tin[u];
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int &t, int p = -1) {
        visited[u] = true;
        tin[u] = low[u] = t++;
        for(int v: adj[u]) {
            if(v == p) continue;
            if(visited[v]) {
                low[u] = min(low[u], tin[v]);
            } else { 
                dfs(v, t, u);
                low[u] = min(low[u], low[v]);
                
                // TODO: change this
                if(is_bridge(u, v)) {
                    cout <<"Bridge: " << u <<" " << v << endl;
                }
            }
        }
    }

    void build() {
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, n+1);
        int t = 0; 
        for(int i = 0; i < n; i++)
            if(!visited[i])
                dfs(i, t);
    }

};
 
int main(){

}
