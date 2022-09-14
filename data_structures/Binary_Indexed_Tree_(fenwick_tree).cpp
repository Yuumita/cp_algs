#include <bits/stdc++.h>
using namespace std;

template<typename T = long long>
struct BIT {
	int N;
	vector<T> tree;

	BIT(int n = -1){
		if(n >= 0) init(n);
	}
	void init(int n){
		N = n;
		tree.assign(N+1, T());	
	}

	template<typename T_array>
	void build(const T_array &a) {
		init(a.size());
		for(int i = 0; i < N; i++)
			add(i, a[i]);
	}


	int g(int i){ return i&(i+1); }
	int h(int i){ return i|(i+1); }

	// add x in position p
	void add(int p, T x){ 
		for(int i = p; i < N; i = h(i))
			tree[i] += x;
	}

	// return A[0] + A[1] + ... + A[r]
	T query(int r){ 
		T sum(); 
		for(int i = r; i >= 0; i = g(i) - 1)
			sum += T[i];	
		return sum;
	}
};



int main(){
	int N, Q; cin >> N >> Q;
	BIT tree(N);
	for(int i=0;i<N;i++){
		int a; cin >> a;
		tree.add(i, a);
	}
	long long a, b, c;
	for(int q=0; q<Q; q++){
		cin >> a >> b >> c;
		if(a==0){
			tree.add(b, c);
		} else{
			cout << tree.query(c-1) - (b==0 ? 0 : tree.query(b-1)) << endl;
		}
	}

	return 0;
}
