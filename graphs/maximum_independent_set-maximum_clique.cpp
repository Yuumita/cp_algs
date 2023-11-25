#include <bits/stdc++.h>
using namespace std;


// Maximum Independent Set of G = Maximum Clique of G^c
struct MaxClique {
    int n;
    // Ng:n -> 2^n, u -> Ng[u]: neighbourhood of u
    vector<int> Ng; 

    // f:2^n -> 2^n, u -> f(u): max clique f(u) s.t f(u) is a subset of u
    vector<int> fdp; 

    MaxClique() {
        init();
    }

    MaxClique(int _n) {
        init(_n);
    }

    void init(int _n = 0) {
        n = _n;
        Ng.assign(n, 0);
        fdp.assign(1<<n, -1);
    }

    void add_edge(int u, int v) {
        Ng[u] |= 1 << v;
        Ng[v] |= 1 << u;
    }

    vector<int> getMaxClique() {
        int S = 0, cnt = 0;
        for(int y = 0; (y << (n/2)) < (1 << n); y++) {
            int Y = (y << (n/2)), ycnt = 0;
            int X = (1 << (n/2)) - 1, xcnt = 0;

            bool is_clique = true;
            for(int u = n/2; u < n; u++) if(Y>>u&1){
                if((Ng[u] & Y | (1 << u)) != Y)
                    is_clique = false;
            }
            if(!is_clique) continue;

            for(int u = n/2; u < n; u++) {
                if(Y >> u & 1) {
                    X &= Ng[u];
                    ycnt++;
                }
            }

            X = f(X);   

            for(int u = 0; u < n/2; u++)
                if(X >> u & 1)
                    xcnt++;
            
            if(xcnt + ycnt > cnt) {
                S = X | Y;
                cnt = xcnt + ycnt;
            }
        }

        vector<int> clique;
        for(int u = 0; u < n; u++) 
            if( S >> u & 1) 
                clique.push_back(u);
        return clique;
    }

    // Computation can become faster using logarithms instead of brute force for u
    int f(int S) {
        if(fdp[S] != -1) return fdp[S];
        if(S == 0) return fdp[S] = 0;

        int u = 0;
        while(u < n && !(S>>u&1)) u++;

        int X = f(S - (1 << u)), Y = f(S & Ng[u]) | (1 << u);
        if(__builtin_popcount(X) > __builtin_popcount(Y))
            return X;
        else 
            return Y;
    }
};



// Following is the computation of independent set
int main() {
    int N, M; cin >> N >> M;

    int G[N][N];
    for(int i = 0; i < N; i++) 
        for(int j = i + 1; j < N; j++)
            G[i][j] = 0;

    for(int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        G[u][v] = 1;
        G[v][u] = 1;
    }

    MaxClique mc(N);
    for(int i = 0; i < N; i++) 
        for(int j = i + 1; j < N; j++)
            if(!G[i][j])
                mc.add_edge(i, j);

    vector<int> out = mc.getMaxClique();
    cout << out.size() << endl;
    for(auto &e: out) cout << e << " ";
    cout << endl;
}