#include <bits/stdc++.h>
using namespace std;

// Note: if there is a cycle, the size of the return will be less than n.
template <typename G = vector<vector<int>>>
vector<int> topological_sort(const G &adj) {
    int n = int(adj.size());
    vector<int> in_degree(n, 0), order;

    for (int i = 0; i < n; i++)
        for (int v : adj[i])
            in_degree[v]++;

    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            order.push_back(i);

    int u = 0;
    while (u < int(order.size())) {
        int node = order[u++];

        for (int v : adj[node])
            if (--in_degree[v] == 0)
                order.push_back(v);
    }

    return order;
}

int main() {
    return 0;
}