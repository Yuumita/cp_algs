#include <bits/stdc++.h>
using namespace std;

template <typename G = vector<vector<int>>>
vector<pair<int, int>> get_cycle(const G& g, bool directed = true) {
    int N = g.size();
    for(int i = 0; i < N; i++) // self loop
        for(auto &j: g[i]) if(i == j)
            return vector<pair<int, int>>(1, {i, i});
    
    vector<int> color(N, 0);
    vector<pair<int, int>> cycle;
    bool found = false;
    auto dfs = [&](auto rec, int u, int p, int r) -> int {
        color[u] = 1;
        for(auto &v: g[u]) {
            if(found) return -1;
            if(!directed && v == p) continue;
            if(color[v] == 1) {
                cycle.emplace_back(u, v);
                return v;
            }
            if(color[v] != 0) continue;
            int end = rec(rec, v, u, r);
            if(end != -1) {
                cycle.emplace_back(u, v);
                if(u == end) {
                    found = true;
                    return -1;
                }
                return end;
            }
        }
        color[u] = 2;
        return -1;
    };

    for(int i = 0; i < N; i++) if(color[i] == 0) {
        dfs(dfs, i, -1, i);
        if(found) {
            reverse(cycle.begin(), cycle.end());
            return cycle;
        }
    }
    return vector<pair<int, int>>{};
}