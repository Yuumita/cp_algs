#include <bits/stdc++.h>
using namespace std;

struct seg_tree {
	int N = 1;
	vector<long long> t;

	void build(vector<long long> &a, int v, int tl, int tr) {
		if(tl == tr) {
			if(tl < a.size()) t[v] = a[tl];
		} else {
			int tm = (tl + tr)/2;
			build(a, 2*v, tl, tm);
			build(a, 2*v+1, tm+1, tr);
			t[v] = t[2*v] + t[2*v+1];
		}
	}

	void resize(int n) {
		N = 1; while(N < n) N <<= 1;
		t.assign(2*N+1, 0);
	}

	seg_tree(int n) { resize(n); }	

	seg_tree(vector<long long> &a) {
		resize(a.size());
		build(a, 1, 0, N-1);
	}	

	int size() { return N; }

	// first call: update(1, 0, tree.size()-1, pos, new_val)
	void update(int v, int tl, int tr, int pos, long long new_val) {
		if(tl == tr) {
			t[v] = new_val;
		} else {
			int tm = (tl + tr)/2;
			if(pos <= tm) 
				update(2*v, tl, tm, pos, new_val);
			else
				update(2*v+1, tm+1, tr, pos, new_val);
			t[v] = t[2*v] + t[2*v+1];
		}
	}

	// first call: update(1, 0, tree.size()-1, l, r)
	long long query(int v, int tl, int tr, int l, int r) {
		if(r < l) return 0;
		if(l == tl && r == tr) 
			return t[v];
		int tm = (tl + tr)/2;
		return query(2*v, tl, tm, l, min(tm, r))
				+ query(2*v+1, tm+1, tr, max(l, tm+1), r);

	}

};

int main(){
	int N, Q; cin >> N >> Q;
	vector<long long> x(N);
	for(auto &e: x) cin >> e;
	seg_tree tree(x);

	while(Q--) {
		int c; cin >> c;
		if(c == 1) {
			int k, u; cin >> k >> u;
			tree.update(1, 0, tree.size()-1, k-1, u);
		} else {
			int a, b; cin >> a >> b;
			cout << tree.query(1, 0, tree.size()-1, a-1, b-1) << endl;
		}
	}


	return 0;
}
