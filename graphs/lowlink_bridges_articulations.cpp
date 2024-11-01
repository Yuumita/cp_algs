#include <bits/stdc++.h>
using namespace std;

/// @brief Compute articulations and bridges
template <typename G = vector<vector<int>>>
class LowLink {
private:
    const G &g;
    int N;
    vector<int> ord, low, articulations;
    vector<pair<int, int>> bridges;
    void dfs(int u, int p, int &t) {
        low[u] = ord[u] = t++;
        int ccnt = 0;
        bool arti = false, parent_skipped = false;
        for(auto &v: g[u]) {
            if(ord[v] == -1) {
                ccnt++;
                dfs(v, u, t);
                low[u] = min(low[u], low[v]);
                arti |= (p != -1) && (low[v] >= ord[u]);
                if(ord[u] < low[v]) bridges.push_back(minmax(u, v));
            } else if(v != p || parent_skipped) {
                low[u] = min(low[u], ord[v]);
            } else {
                parent_skipped = true;
            }
        }
        arti |= (p == -1) && (ccnt > 1);
        if(arti) articulations.push_back(u);
    }
public:
    LowLink(const G &_g) 
        : g(_g), N(_g.size()), ord(_g.size(), -1), low(_g.size(), -1) {
        for(int i = 0, t = 0; i < N; i++) {
            if(ord[i] == -1)
                dfs(i, -1, t);
        }
    }

    vector<pair<int, int>> &get_bridges()  { return bridges; }
    vector<int> &get_articulation_points() { return articulations; }

};

int main(){
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LowLink link(adj);
    for(auto &e: link.get_articulation_points()) {
        cout << e << " ";
    }
    cout << endl;
}