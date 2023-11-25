#include <bits/stdc++.h>
using namespace std;

template <int MOD, bool is_prime = false>
struct modint {
    int v;
    modint(): v(0) {}
    modint(int vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    modint(long long vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    modint(int vv, nullptr_t) : v(vv) {}
    operator int() const { return v; }

    modint& operator+=(modint x) { v += x.v; if(v >= MOD) v -= MOD; return *this; }
    modint& operator++() { if(v == MOD - 1) v = 0; else v++; return *this; }
    modint operator++(int) { modint ans(*this); operator++(); return ans; }
    modint operator-() const { return modint(0) -= *this; }
    modint operator-(modint x) const { return modint(*this) -= x; }
    modint& operator-=(modint x) { if(v < x.v) v += MOD; v -= x.v; return *this; }
    modint& operator--() { if(v == 0) v = MOD - 1; else v--; return *this; }
    modint operator--(int) { modint ans(*this); operator--(); return ans; }
    modint& operator*=(modint x) { v = 1ll * v * x.v % MOD; return *this; }
    modint& operator/=(modint x) { return operator*=(x.inverse()); }

    template<class T> modint operator+(T x) const { return modint(*this) += x; }
    template<class T> modint& operator+=(T x) { return operator+=(modint(x)); }
    template<class T> modint operator-(T x) const { return modint(*this) -= x; }
    template<class T> modint& operator-=(T x) { return operator-=(modint(x)); }
    template<class T> modint operator*(T x) const { return modint(*this) *= x; }
    template<class T> modint& operator*=(T x) { return operator*=(modint(x)); }
    template<class T> modint operator/(T x) const { return modint(*this) /= x; }
    template<class T> modint& operator/=(T x) { return operator/=(modint(x)); }

    modint pow(int n) const {
        modint ret(1), mul(v);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul, n /= 2;
        }
        return ret;
    }
    modint inverse() const {
        // Fermat's Little Theorem
        if(is_prime) return pow(MOD - 2);
        int a = v, b = MOD, u = 1, v = 0, t;
        while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
        }
        return modint(u);
    }

    friend ostream &operator<<(ostream &os, const modint &p) { return os << p.v; }
    friend istream &operator>>(istream &is, modint &a) {
        int t; is >> t;
        a = modint(t);
        return (is);
    }
};

const int MOD = 7340033;
using mint = modint<MOD, true>;

int p = MOD, pw = (1<<20);
mint g = mint(5); // primitive roof of 119(1<<23) + 1

void ntt(vector<mint> &a, bool invert){
	int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        mint wlen = invert ? g.inverse() : g;
        for (int i = len; i < pw; i <<= 1)
			wlen *= wlen;

        for (int i = 0; i < n; i += len) {
            mint w = 1;
            for (int j = 0; j < len / 2; j++) {
                mint u = a[i+j], v = a[i+j+len/2] * w ;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
				w *= wlen;
            }
        }
    }

    if (invert) {
        mint n_1 = mint(n).inverse();
        for (auto & x : a)
			x *= n_1;
    }

	/*
	int n = a.size();
	if(n <= 1) return;

	vector<mint> a0(n/2), a1(n/2);
	for(int i = 0; 2*i < n; i++) {
		a0[i] = a[2*i];
		a1[i] = a[2*i + 1];
	}

	ntt(a0, invert);
	ntt(a1, invert);

	mint w = mint(1), wn =  (invert ? g.inverse() : g);
	for(int i = 0; 2*i < n; i++, w *= wn) {
		a[i]       = a0[i] + w * a1[i];
		a[i + n/2] = a0[i] - w * a1[i];
		if(invert) {
			a[i] /= mint(2); 
			a[i + n/2] /= mint(2);
		}
	}
	*/
}

vector<mint> cyclic_convolution_naive(vector<long long> &a, vector<long long> &b) { 
	vector<mint> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	assert(a.size() == b.size());
	int N = (int)a.size();
	vector<mint> c(N, 0);
	for(int k = 0; k < N; k++) for(int i = 0; i < N; i++) c[k] += a[i] * b[(k-i + N)%N];
	return c;
}

vector<mint> convolution_naive(vector<long long> &a, vector<long long> &b) { 
	vector<mint> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	assert(a.size() == b.size());
	int N = ((int)a.size() + (int)b.size());
	a.resize(N);
	b.resize(N);
	vector<mint> c(N, 0);
	for(int k = 0; k < N; k++) for(int i = 0; i < N && k-i>=0; i++) c[k] += a[i] * b[k-i];
	return c;
}

vector<mint> cyclic_convolution(vector<long long> &a, vector<long long> &b) { 
	vector<mint> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	assert(a.size() == b.size());
	int N = max((int)a.size(), (int)b.size()), n = 1;
	while(n < 2*N) n <<= 1;

	fa.resize(n);
	for(int i = 0; i < (int)a.size(); i++) 
		fa[i + n - a.size()] = fa[i];
	fb.resize(n);

	ntt(fa, false);
	ntt(fb, false);

	for(int i = 0 ; i < n; i++) 
		fa[i] *= fb[i];

	ntt(fa, true);

	vector<mint> c(n);
	for(int i = 0; i < n; i++) c[i] = fa[i];
	while((int)c.size() > N) c.pop_back();
	return c;
}

vector<mint> convolution(vector<long long> &a, vector<long long> &b) { 
	vector<mint> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < a.size() + b.size()) n <<= 1;

	fa.resize(n);
	fb.resize(n);

	ntt(fa, false);
	ntt(fb, false);

	for(int i = 0 ; i < n; i++) 
		fa[i] *= fb[i];

	ntt(fa, true);

	vector<mint> c(n);
	for(int i = 0; i < n; i++) c[i] = fa[i];
	return c;
}

template<class T>
void output_poly(vector<T> &a) {
	for(int k = 0; k < a.size(); k++){
		cout << a[k] << "x^" << k << (k + 1 < a.size() ? " + " : "\n");
	}
}

template<class T> ostream& operator <<(ostream &os, const vector<T> &v) { for(auto &e: v) os << e << " "; return os; }
 
int main(){
	int N; cin >> N;
	vector<long long> A(N), B(N), C;
	for(auto &e: A) cin >> e;
	for(auto &e: B) cin >> e;
	cout << convolution(A, B) << endl;
	cout << convolution_naive(A, B) << endl;
}