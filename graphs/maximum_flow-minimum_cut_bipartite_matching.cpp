#include <bits/stdc++.h>
using namespace std;

/// @brief  Maximum flow class O(n^2m)
template<typename flow_t>
class MaxFlow {
private:
    struct edge {
        int from = 0, to = 0;
        flow_t cap = 0, flow = 0;
        edge(int _from, int _to, flow_t _cap) : from(_from), to(_to), cap(_cap) {}
    };
    int N, M = 0; // vertices, edges
    vector<edge> edges; // edge list
    vector<vector<int>> adj; // adjasency list (with edge id's)
    vector<int> level, ptr;
    queue<int> q;
    bool calculated_flow;

public:
    MaxFlow() : N(0), calculated_flow(false) { }
    MaxFlow(int _N) : N(_N), calculated_flow(false) {
        adj.resize(N);
        level.resize(N);
    }

    void add_edge(int from, int to, flow_t cap = 0) { 
        edges.emplace_back(from, to, cap);
        edges.emplace_back(to, from, 0);
        adj[from].push_back(M++);
        adj[to].push_back(M++);
    }

    // change the (i+1)-th edge added in the class
    void change_edge(int i, flow_t new_cap, flow_t new_flow = 0) {
        assert(new_flow <= new_cap);
        auto &e  = edges[i / 2];
        auto &re = edges[i / 2 + 1];
        e.cap  = new_cap, e.flow = new_flow;
        re.cap = 0, re.flow = -new_flow;
    }

    vector<edge> &get_edges() { return edges; }

private:
    bool bfs(int s, int t) {
        level.assign(N, -1);
        level[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop(); 
            for(auto id: adj[u]) {
                edge &e = edges[id];
                if(level[e.to] == -1 && e.cap - e.flow > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
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
            if(level[e.to] != level[u] + 1 || e.cap - e.flow <= 0)
                continue;

            flow_t f = dfs(e.to, t, min(pushed, e.cap - e.flow));
            if(f <= 0) continue;

            e.flow += f;
            edges[adj[u][cid] ^ 1].flow -= f; 
            return f;
        }
        return 0;
    }

public:

    flow_t flow(int s, int t, flow_t flow_cap = numeric_limits<flow_t>::max()) {
        flow_t F = 0;
        while(flow_cap > 0 && bfs(s, t)) {
            ptr.assign(N, 0);
            flow_t dF = dfs(s, t, flow_cap);
            assert(dF > 0);
            F += dF,
            flow_cap -= dF;
        }
        return F;
    }
    
    vector<bool> min_cut(int s, int t, flow_t flow_cap = numeric_limits<flow_t>::max()) {
        flow(s, t);
        vector<bool> scut(N);
        q.push(s);
        scut[s] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(auto &id: adj[u]) {
                edge &e = edges[id];
                if(scut[e.to] == false && e.cap - e.flow > 0) {
                    q.push(e.to);
                    scut[e.to] = true;
                }
            }
        }
        return scut;
    } 

};


class BipartiteGraph {
private:
    MaxFlow<long long> mf;
    int N, M, s, t;
    bool calculated;

public:
    BipartiteGraph(int _N, int _M): 
        N(_N), M(_M), s(N+M), t(N+M+1), calculated(false) {
        mf = MaxFlow<long long>(N+M+2);
        for(int i = 0; i < N; i++) mf.add_edge(s, i, 1);
        for(int i = 0; i < M; i++) mf.add_edge(i + N, t, 1);
    }

    void add_edge(int from, int to, long long cap = 1) {
        assert(0 <= from && from < N);
        assert(0 <= to && to < M);
        mf.add_edge(from, to + N, cap);
    }

    long long flow() {
        calculated = true;
        return mf.flow(s, t);
    }

    vector<pair<int, int>> maximum_matching() {
        if(!calculated) flow();
        vector<pair<int, int>> ret;
        for(auto &e: mf.get_edges()) {
            if(e.flow > 0 && e.from != s && e.to != t) {
                ret.emplace_back(e.from, e.to - N);
            }
        }
        return ret;
    }

    // pair<vector<int>, vector<int>> minimum_vertex_cover() { }

};

 
int main(){
    // int n, m; cin >> n >> m;
    // MaxFlow<long long> gf(n);
    // for(int i = 0; i < m; i++) {
    //     int a, b; cin >> a >> b; a--, b--;
    //     long long c; cin >> c;
    //     gf.add_edge(a, b, c);
    // }
    // cout << gf.flow(0, n-1) << endl;
    // vector<bool> scut = gf.min_cut(0, n-1);
    // for(int i=0;i<n;i++) cout << scut[i] << " ";
    // cout << endl;
    int L, R, M; cin >> L >> R >> M;
    BipartiteGraph bg(L, R);
    for(int i = 0 ; i < M; i++) {
        int a, b; cin >> a >> b;
        bg.add_edge(a, b);
    }
    vector<pair<int, int>> match = bg.maximum_matching();
    cout << match.size() << endl;
    for(auto &p: match) {
        cout << p.first << " " << p.second << endl;
    }
}