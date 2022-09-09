#include <bits/stdc++.h>
using namespace std;

struct lazy_seg {
	int N = 1;
	vector<long long> t;
	vector<bool> marked;

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
		marked.assign(2*N+1, false);
	}

	seg_tree(int n) { resize(n); }	

	seg_tree(vector<long long> &a) {
		resize(a.size());
		build(a, 1, 0, N-1);
	}	

	int size() { return N; }

	void push(int v) {
		if (marked[v]) {
			t[v*2] = t[v*2+1] = t[v];
			marked[v*2] = marked[v*2+1] = true;
			marked[v] = false;
		}
	}

	// first call: update(1, 0, tree.size()-1, pos, new_val)
	void update(int v, int tl, int tr, int l, int r, int new_val) {
		if (l > r) 
			return;
		if (l == tl && tr == r) {
			t[v] = new_val;
			marked[v] = true;
		} else {
			push(v);
			int tm = (tl + tr) / 2;
			update(v*2, tl, tm, l, min(r, tm), new_val);
			update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
		}
	}

	int get(int v, int tl, int tr, int pos) {
		if (tl == tr) {
			return t[v];
		}
		push(v);
		int tm = (tl + tr) / 2;
		if (pos <= tm) 
			return get(v*2, tl, tm, pos);
		else
			return get(v*2+1, tm+1, tr, pos);
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
