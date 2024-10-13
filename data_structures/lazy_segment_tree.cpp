#include <bits/stdc++.h>
using namespace std;

template <class S, 
		  S (*op)(S, S),
		  S (*e)(),
		  class F,
		  S (*mapping)(F, S),
		  F (*composition)(F, F),
		  F (*id)()>
class lazy_segtree {
private: 
	int n, N, log;
	vector<S> tree;
	vector<F> lazy;
	void update(int k) { tree[k] = op(tree[2*k], tree[2*k+1]); }
	void all_apply(int k, F f) {
		tree[k] = mapping(f, tree[k]);
		if(k < N) lazy[k] = composition(f, lazy[k]);
	}
	void push(int k) {
		all_apply(2*k, lazy[k]);
		all_apply(2*k + 1, lazy[k]);
		lazy[k] = id();
	}
public:

	S get(int p) const {
		assert(0 <= p && p < n);
		p += N;
		for(int i = log; i >= 1; i--) push(p >> i);
		return tree[p];
	}

	void set(int p, S x) {
		assert(0 <= p && p < n);
		p += N;
		for(int i = log; i >= 1; i--) push(p >> i);
		tree[p] = x;
		for(int i = 1; i <= log; i++) update(p >> i);
	}

	// inclusive, 0-indexed
	S prod(int l, int r) const {
		assert(0 <= l && l <= r && r < n);
		l += N, r += N + 1; // now r becomes non-inclusive
		for(int i = log; i >= 1; i--) {
			if(((l>>i)<<i) != l) push(l >> i);
			if(((r>>i)<<i) != r) push((r-1) >> i);
		}
		S lv = e(), rv = e();
		while(l < r) {
			if(l & 1) lv = op(lv, tree[l++]);
			if(r & 1) rv = op(tree[--r], rv);
			l >>= 1, r >>= 1;
		}
		return op(lv, rv);
	}

	S all_prod() const { return tree[1]; }

	void apply(int p, F f) {
		assert(0 <= p && p < n);
		p += N;
		for(int i = log; i >= 1; i--) push(p >> i);
		tree[p] = mapping(f, tree[p]);
		for(int i = 1; i <= log; i++) update(p >> i);
	}

	// inclusive
	void apply(int l, int r, F f) {
		assert(0 <= l && l <= r && r < n);
		l += N, r += N + 1; // now r becomes non-inclusive
		for(int i = log; i >= 1; i--) {
			if(((l>>i)<<i) != l) push(l >> i);
			if(((r>>i)<<i) != r) push((r-1) >> i);
		}

		int lprev = l, rprev = r;
		while(l < r) {
			if(l & 1) all_apply(l++, f);
			if(r & 1) all_apply(--r, f);
			l >>= 1;
			r >>= 1;
		}
		l = lprev, r = rprev;

		for(int i = 1; i <= log; i++) {
			if(((l>>i)<<i) != l) update(l >> i);
			if(((r>>i)<<i) != r) update((r-1) >> i);
		}
	}

	lazy_segtree(): lazy_segtree(0) {}
	lazy_segtree(int _n) : lazy_segtree(vector<S>(_n, e())) {}
	lazy_segtree(const vector<S> &v) : n(v.size()) {
		N = 1, log = 0;
		while(N < n) {
			N <<= 1, log++;
		}
		tree.assign(2*N, e());
		lazy.assign(N, id());
		for(int i = 0; i < n; i++) tree[N + i] = v[i];
		for(int i = N-1; i >= 1; i--) {
			update(i);
		}
	}

};

int main(){
	return 0;
}
