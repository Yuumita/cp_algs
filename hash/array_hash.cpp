#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb  push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define forn(i,l,r) for(int (i)=(l); (i)<(r); (i)++)
#define rinc(i,l,r) for(int (i)=(l); (i)<=(r); (i)++)
#define rdec(i,r,l) for(int (i)=(r); (i)>=(l); (i)--)
const int mod = 1e9 + 7, inf = 2e9+5, nn = 2e6;

template<typename T>
struct array_hash {
	using hash_t = uint64_t;

	long long n, p = 31, m = 1e9 + 7, pinv = 129032259;
	vector<T> array;
	hash_t hash;

	array_hash(int _n = 0) {
		init(_n);
	}

	array_hash(const vector<T> &_array) {
		init(_array);
	}

	hash_t get_hash(int i) const {
		return (1ll * array[i%n] * pow(p, i));
	}

	void compute_hash() {
		hash = 0;
		for(long long pp = 1, i = 0; i < n; pp = (pp * p) % m, i++) {
			hash = (hash + 1ll * array[i%n] * pp % m) % m;
		}
	}

	void init(int _n) {
		n = _n;
		array.assign(n, 0);
		compute_hash();
	}

	void init(const vector<T> &_array) {
		array = _array;
		n = int(array.size());
		compute_hash();
	}

	const T& operator[](int index) const {
		return array[index];
	}

	void modify(int i, const T &val) {
		hash -= get_hash(i);
		array[i%n] = val;
		hash += get_hash(i);
	}

    long long pow(long long a, int n) const {
		long long res = 1;
		while(n > 0) {
			if(n % 2) res = (res * a) % m;
			a = (a * a) % m;
			n /= 2;
		}
        return res;
    }
};


void solve(){
}
 
int main(){
}