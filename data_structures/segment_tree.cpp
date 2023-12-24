#include <bits/stdc++.h>
using namespace std;

// type, identity element
template<typename T = long long, T (*e)() = T(0)>
struct seg_tree {
	int N = 1;
	vector<T> t;

	void op(T x, T y) {
		return x + y;
	}

	void build(vector<T> &a, int v, int tl, int tr) {
		if(tl == tr) {
			if(tl < a.size()) t[v] = a[tl];
		} else {
			int tm = (tl + tr)/2;
			build(a, 2*v, tl, tm);
			build(a, 2*v+1, tm+1, tr);
			t[v] = op(t[2*v], t[2*v+1]);
		}
	}

	int size() { return N; }
	void resize(int n) {
		N = 1; while(N < n) N <<= 1;
		t.assign(2*N+1, e());
	}
	seg_tree(int n) { resize(n); }	
	seg_tree(vector<T> &a) {
		resize(a.size());
		build(a, 1, 0, N-1);
	}	


	void _update(int v, int tl, int tr, int p, T x) {
		if(tl == tr) {
			t[v] = x;
		} else {
			int tm = (tl + tr)/2;
			if(pos <= tm) 
				_update(2*v, tl, tm, p, x);
			else
				_update(2*v+1, tm+1, tr, p, x);

			t[v] = op(t[2*v], t[2*v+1]);
		}
	}

	T _query(int v, int tl, int tr, int l, int r) {
		if(r < l) 
			return e();
		if(l == tl && r == tr) 
			return t[v];

		int tm = (tl + tr)/2;
		return op(_query(2*v, tl, tm, l, min(tm, r)),
				_query(2*v+1, tm+1, tr, max(l, tm+1), r));
	}

	T get(int p) { // To be tested
		if(!(0 <= p && p < N)) return e();
		return t[p + N];
	}

	void set(int pos, T new_val) {
		_update(1, 0, size()-1, pos, new_val);
	}

	T query(int l, int r) {
		return _query(1, 0, size()-1, l, r);
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
