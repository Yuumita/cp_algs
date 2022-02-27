#include <bits/stdc++.h>
using namespace std;

struct BIT {
	int N;
	vector<long long> T;
	BIT(int n = 0){
		N = n;
		T.assign(n, 0);	
	}
	void resize(int n){
		N = n;
		T.assign(n, 0);	
	}

	int g(int i){ return i&(i+1); }
	int h(int i){ return i|(i+1); }

	void add(int p, long long x){ // add x in position p
		for(int i = p; i < N; i = i|(i+1))
			T[i] += x;
	}
	long long query(int r){ // return A[0] + A[1] + ... + A[r]
		long long ret = 0;
		for(int i = r; i >= 0; i = (i&(i+1)) - 1){
			ret += T[i];	
		}
		return ret;
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
