#include <bits/stdc++.h>
using namespace std;

template<typename flow_t>
struct dinic {

    struct edge { // edge u --> v
        int u = 0, v = 0;
        flow_t capacity = 0, flow = 0;
        edge(int u_, int v_, flow_t capacity_) : u(u_), v(v_), capacity(capacity_) {}
    };

    int n, m = 0; // vertices, edges
    vector<edge> edges; // edge list
    vector<vector<int>> adj; // adjasency list
    vector<int> level, ptr;
    queue<int> q;


    dinic(int nn) : n(nn) {
        adj.resize(n);
        level.resize(n);
    }

    void add_edge(int u, int v, flow_t cap = 0) { 
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop(); 
            for(auto id: adj[u]) {
                edge &e = edges[id];
                if(level[e.v] == -1 && e.capacity - e.flow > 0) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[t] != -1;
    }

    flow_t dfs(int u, int t, flow_t pushed) {
        if(pushed == 0) return 0;
        if(u == t) return pushed;
        for(auto &cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
            edge &e = edges[adj[u][cid]];
            if(level[e.v] != level[u] + 1 || e.capacity - e.flow <= 0)
                continue;

            flow_t f = dfs(e.v, t, min(pushed, e.capacity - e.flow));
            if(f <= 0) continue;

            e.flow += f;
            // complementary edge (in the Residual Network), should probably do it another way
            edges[adj[u][cid] ^ 1].flow -= f; 
            return f;
        }
        return 0;
    }

    flow_t flow(int s, int t, flow_t flow_cap = numeric_limits<flow_t>::max()) {
        flow_t F = 0;
        while(flow_cap > 0 && bfs(s, t)) {
            ptr.assign(n, 0);
            flow_t dF = dfs(s, t, flow_cap);
            assert(dF > 0);
            F += dF,
            flow_cap -= dF;
        }
        return F;
    }
    
    void clear_flow() {
        for(auto &e: edges) e.flow = 0;
    }

    vector<bool> get_min_cut(int s, int t, flow_t flow_cap = numeric_limits<flow_t>::max()) {
        flow(s, t, flow_cap);

        vector<bool> scut(n);
        q.push(s);
        scut[s] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(auto &id: adj[u]) {
                edge &e = edges[id];
                if(scut[e.v] == false && e.capacity - e.flow > 0) {
                    q.push(e.v);
                    scut[e.v] = true;
                }
            }
        }

        return scut;
    } 

};

 
int main(){
    int n, m; cin >> n >> m;
    dinic<long long> gf(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--, b--;
        long long c; cin >> c;
        gf.add_edge(a, b, c);
    }
    cout << gf.flow(0, n-1) << endl;
    vector<bool> scut = gf.get_min_cut(0, n-1);
    for(int i=0;i<n;i++) cout << scut[i] << " ";
    cout << endl;
}