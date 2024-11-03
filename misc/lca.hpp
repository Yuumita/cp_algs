#include <bits/stdc++.h>
using namespace std;

#include "rmq.hpp"

class LCA {
public:
    LCA(int _n = 0) : n(_n), adj(vector<vector<int>>(n, vector<int>())) {}
    LCA(const vector<vector<int>> &_adj) : n(_adj.size()) {
        adj = _adj;
        build();
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
        for(int v: adj[u]) if(v != p) {
            dfs0(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }

    // euler tour to prepare for rmq in depths
    void tour_dfs(int u) {
        first_occurence[u] = int(euler.size());
        euler.push_back(u);
        for(auto v: adj[u]) if(v != parent[u]) {
            tour_dfs(v);
            euler.push_back(u);
        }
    }

    void build(int root = 0, bool build_rmq = true) {
        assert(0 <= root && root < n);
        subtree_size.resize(n);
        parent.assign(n, -1);
        depth.assign(n, -1);
        euler.clear();
        first_occurence.resize(n);

        dfs0(root, -1);
        for(int i = 0; i < n; i++)
            if(depth[i] < 0)
                dfs0(i, -1);

        for(int i = 0; i < n; i++) {
            if(parent[i] < 0 ) tour_dfs(i);
            euler.push_back(-1);
        }

        vector<int> euler_depths;
        for(int u: euler) 
            euler_depths.push_back(u < 0 ? u : depth[u]);


        if(build_rmq)
            rmq.init(euler_depths);

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

private:
    int n = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree_size;
    vector<int> euler, first_occurence;
    RMQ<int> rmq;
    bool built;
};