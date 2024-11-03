#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
	DSU() : N(0), components(0) {}
	DSU(int n) : N(n), parent_size(n, -1), components(N) {}

	int leader(int u){
		assert(0 <= u && u < N);
		if(parent_size[u] < 0) return u;
		return parent_size[u] = leader(parent_size[u]);
	}

	bool same(int u, int v) {
		assert(0 <= u && u < N);
		assert(0 <= v && v < N);
		return leader(u) == leader(v);
	}

	int size(int u) {
		assert(0 <= u && u < N);
		return -parent_size[leader(u)];
	}

	// reterns the representative of the merged set
	int merge(int u, int v){ 
		assert(0 <= u && u < N);
		assert(0 <= v && v < N);
		u = leader(u), v = leader(v);
		if(u == v) return u;
		if(-parent_size[u] < -parent_size[v]) swap(u, v); // ensure size(u) >= size(v)
		parent_size[u] += parent_size[v];
		parent_size[v] = u;
		components--;
		return u;
	}

	vector<vector<int>> groups() {
        vector<vector<int>> g(N, vector<int>());
        for (int i = 0; i < N; i++) {
            g[leader(i)].push_back(i);
        }
        g.erase(
            remove_if(g.begin(), g.end(),
						[&](const vector<int>& v) { return v.empty(); }),
            g.end());
        return g;
	}

private:
	int N;
	int components;
	vector<int> parent_size; // parent_size[i] < 0 => size[i], else => parent[i]
};
