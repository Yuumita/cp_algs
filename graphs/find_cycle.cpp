#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb  push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define forn(i,l,r) for(int i=l; i<r; i++)
const int MOD = 1e9 + 7, INF = 2e9+5, NN = 2e6;

vector<vector<int>> adj;
vector<int> visited, parent;
int cycle_start = -1, cycle_end = -1;

bool dfs(int u, int p){
    visited[u] = 1;
    for(auto v: adj[u]){
        if(v == p) continue;
        if(visited[v]) {
            cycle_start = v;
            cycle_end = u;
            return true;
        }
        parent[v] = u;
        if(dfs(v, u))
            return true;
    }
    return false;
}

int main(){
    int n, m; cin >> n >> m;
    visited.assign(n, 0); 
    parent.assign(n, -1);
    adj.resize(n);
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b; a--, b--; // 0-indexed nodes
        adj[a].push_back(b); adj[b].push_back(a);
    }

    for(int i = 0; i < n; i++)
        if(!visited[i])  if(dfs(i, -1)) break;
    
    if(cycle_end == -1){
        cout << "IMPOSSIBLE";
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for(int u = cycle_end; u != cycle_start; u = parent[u])
            cycle.push_back(u);
        cycle.push_back(cycle_start);
        cout << cycle.size() << endl;
        for(auto u : cycle)
            cout << u+1 << " "; 
    }

}	
