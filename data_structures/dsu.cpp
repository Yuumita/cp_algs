#include <bits/stdc++.h>
using namespace std;

struct DSU{
	int N;
	vector<int> p, sz;
	vector<vector<int>> g;
	DSU(int n){
		N = n;
		g.assign(n, vector<int> ());		
		p.resize(n); sz.assign(n, 1);
		for(int i=0;i<n;i++) p[i] = i;
	}
	void resize(int n){
		N = n;
		g.assign(n, vector<int> ());		
		p.resize(n); 
		for(int i=0;i<n;i++) p[i] = i;
	}

	void merge(int u, int v){ // merging u to v
		int fu = f(u), fv = f(v);
		if(sz[fu] > sz[fv])
			return merge(v, u);
			
		sz[fv] += sz[fu];
		p[fu] = fv;
	}
	int f(int u){
		if(p[u] == u) return u;
		return p[u] = f(p[u]);
	}
};

int main(){
	int N, Q; cin >> N >> Q;
	int t[Q], u[Q], v[Q];
	DSU dsu(N);
	for(int i=0;i<Q;i++){
		cin >> t[i] >> u[i] >> v[i];
		if(t[i]){
			cout << (dsu.f(u[i]) == dsu.f(v[i])) << endl;			
		} else {
			dsu.merge(u[i], v[i]);
		}
	}
	return 0;
}
