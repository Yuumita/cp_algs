#include <bits/stdc++.h>
using namespace std;

struct DSU {
	int components = 0;
	vector<int> parent, size;

	DSU(int n = -1){
		if(n >= 0) init(n);
	}

	void init(int n){
		components = n;
		size.assign(n+1, 1);
		parent.resize(n+1); 
		iota(parent.begin(), parent.end(), 0);
	}

	int find(int u){
		return u == parent[u] ? u : parent[u] = find(parent[u]);
	}

	// merging u to v, returns false if they were connected (true if merged succesfully)
	bool merge(int u, int v){ 
		u = find(u), v = find(v);
		if(u == v) return false;

		if(size[u] > size[v]) swap(u, v); 

		parent[u] = v;
		size[v] += size[u];
		components--;
		return true;
	}
};

int main(){
	int N, Q; cin >> N >> Q;
	int t[Q], u[Q], v[Q];
	DSU dsu(N);
	for(int i=0;i<Q;i++){
		cin >> t[i] >> u[i] >> v[i];
		if(t[i]){
			cout << (dsu.find(u[i]) == dsu.find(v[i])) << endl;			
		} else {
			dsu.merge(u[i], v[i]);
		}
	}
	return 0;
}
