#include <bits/stdc++.h>
using namespace std;

struct DSU{
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

template<typename weight_t = int>
struct MST {
    // u <--> v
    struct edge {
        int u, v;
        weight_t w;
        int i = -1;
        bool in_tree = false;

        edge(int uu, int vv, weight_t ww, int ii = -1) 
            : u(uu), v(vv), w(ww), i(ii) {}
        edge() {}

        bool operator<(const edge &other) const {
            return w < other.w;
        }
    };

    DSU dsu;
    vector<edge> edges;
    vector<bool> in_mst;

    MST(int n = -1) {
        if(n >= 0) init(n);
    }

    void init(int n) {
        dsu.init(n);
        edges = {};
        in_mst = {};
    }

    void add_edge(int u, int v, weight_t w) {
        edges.emplace_back(u, v, w, int(edges.size()));
        in_mst.push_back(false); 
    }

    vector<int> get_mst() {
        sort(edges.begin(), edges.end());
        vector<int> res;

        for(auto &e: edges) {
            if(dsu.merge(e.u, e.v)) {
                in_mst[e.i] = true;
                res.push_back(e.i);
                e.in_tree = true;
            }
        }
        
        return res;
    }

};

int main(){
    int n, m; cin >> n >> m;
    MST<int> mst(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--, v--;
        mst.add_edge(u, v, w);
    }

    vector<int> tree = mst.get_mst();

    for(auto &ei: tree) {
        cout << ei+1 <<" ";
    }
    cout << endl;

	return 0;
}
