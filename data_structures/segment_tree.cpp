#include <bits/stdc++.h>
using namespace std;

template<class S = long long>
class segtree {
public:
	S op(S a, S b) const { // binary operation between monoids
		return a + b;
	}
	S e() const { // identity element
		return S(0);
	}
private: 
	int n, N, log;
	vector<S> tree;
	void update(int k) {
		tree[k] = op(tree[2*k], tree[2*k+1]);
	}
public:

	S get(int p) const {
		assert(0 <= p && p < n);
		return tree[p + N];
	}

	void set(int p, S x) {
		assert(0 <= p && p < n);
		p += N;
		tree[p] = x;
		for(int i = 1; i <= log; i++) update(p >> i);
	}

	// inclusive, 0-indexed
	S prod(int l, int r) const {
		assert(0 <= l && l <= r && r < n);
		S lv = e(), rv = e();
		l += N, r += N + 1; // now r becomes non-inclusive
		while(l < r) {
			if(l & 1) lv = op(lv, tree[l++]);
			if(r & 1) rv = op(tree[--r], rv);
			l >>= 1, r >>= 1;
		}
		return op(lv, rv);
	}

	S all_prod() const { return tree[1]; }

	segtree(): segtree(0) {}
	segtree(int _n) : segtree(vector<S>(_n, e())) {}
	segtree(const vector<S> &v) : n(v.size()) {
		N = 1, log = 0;
		while(N < n) {
			N <<= 1, log++;
		}
		tree.assign(2*N, e());
		for(int i = 0; i < n; i++) tree[N + i] = v[i];
		for(int i = N-1; i >= 1; i--) {
			update(i);
		}
	}

};

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &(a[i]));
    }

    segtree<long long> seg(a);

	while(q--) {
		int t; cin >> t;
		if(t == 0) {
			int p, x; cin >> p >> x;
			seg.set(p, seg.get(p) + x);
		} else {
			int l, r; cin >> l >> r;
			cout << seg.prod(l, r-1) << endl;
		}
	}
}