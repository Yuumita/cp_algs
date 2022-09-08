#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb  push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define forn(i,l,r) for(int (i)=(l); (i)<(r); (i)++)
#define rinc(i,l,r) for(int (i)=(l); (i)<=(r); (i)++)
#define rdec(i,r,l) for(int (i)=(r); (i)>=(l); (i)--)
const int MOD = 1e9 + 7, INF = 2e9+5, NN = 2e6;

struct query {
	int u, k, i;
	query(int UU, int KK, int ii) {
		u = UU, k = KK, i = ii;
	}
};

int N;
vector<vector<int>> adj;
int U[NN], K[NN], depth[NN];
vector<vector<int>> QI;
vector<int> I;
vector<query> P; 
vector<map<int, int>> D;


void dfs0(int u, int p) {
	if(p != -1) depth[u] = depth[p] + 1;
	D[u][depth[u]] = u;

	if(p != -1 && adj[u].size() <= 1) { // leaf
		I[u] = u;
		continue;
	} 

	for(auto v: adj[u]) if(p != v){
		dfs0(v, u);
	}

	sort(all(adj[u]), [&](const int a, const int b){
		if(a == p || b == p) return a == p;
		return D[a].size() < D[b].size();
	});

	for(int ci = 1; ci < (int)adj[u].size(); ci++) {
		int j = (int)adj[u].size() - 1;
		if(ci == j) j--;
		if(j < 1) continue;
		int v = adj[u][ci];
		for(auto q: P[I[v]]) {
			int d1 = depth[q.u] - depth[u] + 1;
			int d2 = k - d1;
			if(D[u].find(d2) != D[u].end()) {
				ans[q.i] = D[u][d2];
			}
		}
	}

	I[u] = I[adj[u].back()];
	for(int j = (int)adj[u].size() - 2; j >= 1; j--) {
		int v = adj[u][j];
		for(auto q: P[v]) {
			if(ans[q.i] == -1) {
				P[I[u]].pb(q);
			}
		}
	}

	int s = -1;
	for(auto v: adj[u]) if(p != v){
		if(s == -1 || P[v].size() < P[s].size()) s = v;
	}

}


int main(){
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	cin >> N;
	adj.resize(N);
	I.resize(N);
	D.resize(N);


	forn(i,0,N-1) {
		int A, B; cin >> A >> B; A--, B--;
		adj[A].pb(B);
		adj[B].pb(A);
	}



	int Q; cin >> Q;

	ans.assign(Q, -1);

	while(Q--){ 
		cin >> U[i] >> K[i]; U[i]--;
	}	

	depth[0] = 0;
	dfs0(0, -1);
}