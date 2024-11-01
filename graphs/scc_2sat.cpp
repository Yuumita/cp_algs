#include <bits/stdc++.h>
using namespace std;

// new graph: SCC.gSCC, new node of k: SCC[k], component of i: scc.belong(i)
template <typename G = vector<vector<int>>>
class SCC {
private:
    int N;
    const G &g;
    vector<int> order, roots, root_nodes, comp;
    vector<bool> used;
    vector<vector<int>> blng;

public:
    G gT, gSCC;
    
    SCC(const G &_g) : g(_g), used(_g.size(), false), N(_g.size()) { 
        build(); 
    }

    int operator[](int k) { return comp[k]; }
    vector<int> &belong(int i) { return blng[i]; }
    size_t size() { return gSCC.size(); }


    void dfs(int u) {
        if(used[u]) return;
        used[u] = true;
        for(auto &v: g[u]) dfs(v);
        order.push_back(u);
    }

    void rdfs(int u, int cc) {
        if(comp[u] != -1) return;
        comp[u] = cc;
        for(auto &v: gT[u]) rdfs(v, cc);
    }

    void build() {
        for(int i = 0; i < N; i++) dfs(i);
        reverse(order.begin(), order.end());
        used.clear();

        comp.resize(N, -1);

        gT.resize(N);
        for(int i = 0; i < N; i++) {
            for(auto &e: g[i]) {
                gT[e].emplace_back(i);
            }
        }

        int ccnt = 0;
        for(int i: order) if(comp[i] == -1) {
            rdfs(i, ccnt);
            ccnt++;
        }

        gSCC.resize(ccnt);
        blng.resize(ccnt);
        for(int i = 0; i < N; i++) {
            blng[comp[i]].push_back(i);
            for(auto &j: g[i]) {
                int A = comp[i], B = comp[j];
                if(A != B) gSCC[A].push_back(B);
            }
        }

    }

};

int main () {
    int N, M; cin >> N >> M;
    vector<vector<int>> g(N, vector<int>());
    for(int j = 0; j < M; j++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    SCC scc(g);
    cout << scc.size() << endl;
    for(int i = 0; i < scc.size(); i++) {
        cout << scc.belong(i).size() << " ";
        for(int j: scc.belong(i)) cout << j << " ";
        cout << endl;
    }
    return 0;
}