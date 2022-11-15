#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n;
    vector<vector<int>> adj, adj_T, adj_SCC; // adjacency list and transpose, adj of condensation graph
    vector<int> order, roots, root_nodes;
    vector<bool> used;
    vector<vector<int>> components;
    vector<int> component;

    void dfs_compute(int u) {
        used[u] = true;

        for(auto v: adj[u]) 
            if(!used[v]) dfs_compute(v);

        order.push_back(u);
    }

    void dfs(int u) {
        used[u] = true;
        component.push_back(u);

        for(auto v: adj_T[u]) 
            if(!used[u]) dfs(v);
    }

    void init(int n = 0) {
        adj.resize(n);
    }

    // Add an edge u --> v
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj_T[v].push_back(u);
    }

    SCC() {
        init(0);     
    }

    SCC(int n_) {
        if(n_ < 0) n = 0;
        init(n_);     
    }

    void compute_components() { 
        used.assign(n, false);

        for(int i = 0; i < n; i++) 
            if(!used[i]) dfs_compute(i);

        used.assign(n, false);
        reverse(order.begin(), order.end());

        for(auto u: order) {
            if(!used[u]) {
                dfs(u);                

                int root = component.front();
                for(auto v: component) roots[v] = root;
                root_nodes.push_back(root);

                components.push_back(component);
                component.clear();
            }
        }

        for(int u = 0; u < n; u++) {
            for(auto v: adj[u]) {
                if(roots[u] != roots[v])
                    adj_SCC[roots[u]].push_back(roots[v]);
            }
        }

    }


};

int main () {
    return 0;
}