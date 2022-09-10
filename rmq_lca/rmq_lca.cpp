#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1647

template<typename T, bool minimum = true>
struct RMQ {
    int n = 0, K = 25; // array size, maximum power of 2
    vector<T> v; // values
    vector<int> log; // logarithm precomputation
    // index of better value (sparse table index)
    vector<vector<int>> spi; 

    RMQ(const vector<T> &v0 = {}) {
        if(int(v0.size()) > 0) build(v0);
    }

    // if v[i] == v[j] returns j
    int better_index(int i, int j) {
        return (minimum ? v[i] < v[j] : v[i] > v[j]) ? i : j;
    }

    void build(const vector<T> &v0) {
        n = v0.size();
        K = max((n == 0 ? -1: 31 - __builtin_clz(n)) + 1, K);

        v.resize(n);
        spi.assign(n, vector<int> (K+1));
        log.resize(n + 1);
        log[1] = 0;
        for(int i = 2; i <= n; i++) log[i] = log[i/2] + 1;


        for(int i = 0; i < n; i++) v[i] = v0[i];
        for(int i = 0; i < n; i++) spi[i][0] = i;
        for(int j = 1; j <= K; j++)
            for(int i = 0; i + (1 << j) - 1 < n; i++) 
                spi[i][j] = better_index(spi[i][j-1], spi[i + (1 << (j-1))][j-1]);
            
    }

    // Returns minarg v[L..R], (ties broken with bigger index)
    int query_index(int L, int R) {
        assert(0 <= L && R < n);
        int j = log[R - L + 1];
        return better_index(spi[L][j], spi[R - (1 << j) + 1][j]);
    }

    // Returns min v[L...R]
    T query(int L, int R) {
        return v[query_index(L, R)];
    }

};

struct LCA {
    int n = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree_size;
    vector<int> euler, first_occurence;
    RMQ<int> rmq;
    bool built;

    LCA(int _n = 0) { init(_n); }
    LCA(const vector<vector<int>> &_adj) {
        init(_adj);
    }


    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        subtree_size.resize(n);
        first_occurence.resize(n);
    }

    void init(const vector<vector<int>> &_adj) {
        init(_adj.size());
        adj = _adj;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // precompute parent, depth, subtree_size
    void dfs0(int u, int p) {
        parent[u] = p;
        depth[u] = p < 0 ? 0 : depth[p] + 1;
        subtree_size[u] = 1;
        for(auto v: adj[u]) if(v != p) {
            dfs0(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }

    // euler tour to prepare for rmq in dephts
    void tour_dfs(int u) {
        first_occurence[u] = int(euler.size());
        euler.push_back(u);
        for(auto v: adj[u]) if(v != parent[u]) {
            tour_dfs(v);
            euler.push_back(u);
        }
    }


    void build(int root = 0, bool build_rmq = true) {
        parent.assign(n, -1);
        depth.assign(n, -1);

        if(0 <= root && root < n) dfs0(root, -1);

        for(int i = 0; i < n; i++)
            if(i != root && parent[i] < 0)
                dfs0(i, -1);

        for(int i = 0; i < n; i++) {
            if(parent[i] < 0 ) tour_dfs(i);
            euler.push_back(-1);
        }

        vector<int> euler_depths;
        for(int u: euler) 
            euler_depths.push_back(u < 0 ? u : depth[u]);


        if(build_rmq)
            rmq.build(euler_depths);

        built = true; 
    }


    // returns -1 if u and v are not connected
    int lca(int u, int v) {
        int ui = first_occurence[u], vi = first_occurence[v];
        if(ui > vi) swap(ui, vi);
        return euler[rmq.query_index(ui, vi)];
    }

    // returns distance(u, v)
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u, v)];
    }

    int get_subtree_size(int u) { return subtree_size[u]; }


};


int main(){
    int n, q; cin >> n >> q;
    LCA tree(n);
    for(int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--, b--;
        tree.add_edge(a, b);
    }
    tree.build();
    while(q--) {
        int a, b; cin >> a >> b; a--, b--;
        cout << tree.dist(a, b) << endl;
    }
}