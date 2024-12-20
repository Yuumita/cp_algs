#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert){
	int n = a.size();
	if(n <= 1) return;
	vector<cd> a0(n/2), a1(n/2);
	for(int i = 0; 2*i < n; i++) {
		a0[i] = a[2*i];
		a1[i] = a[2*i + 1];
	}

	fft(a0, invert);
	fft(a1, invert);

	double angle = 2 * PI / n * (invert ?  -1 : +1);
	cd w(1), we(cos(angle), sin(angle));
	for(int i = 0; 2*i < n; i++, w *= we) {
		a[i]       = a0[i] + w * a1[i];
		a[i + n/2] = a0[i] - w * a1[i];
		if(invert) {
			a[i] /= 2; 
			a[i + n/2] /= 2;
		}
	}
}

vector<long long> convolution(vector<long long> &a, vector<long long> &b) { 
	if(a.size() == 0 || b.size() == 0) return {};
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < a.size() + b.size()) n <<= 1;

	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);

	for(int i = 0 ; i < n; i++) 
		fa[i] *= fb[i];

	fft(fa, true);

	vector<long long> c(n);
	for(int i = 0; i < n; i++) c[i] = round(fa[i].real());
	c.resize(a.size() + b.size() - 1);
	return c;
}


vector<long long> cyclic_convolution_naive(vector<long long> &a, vector<long long> &b) { 
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	assert(a.size() == b.size());
	int N = (int)a.size();
	vector<long long> c(N, 0);
	for(int k = 0; k < N; k++) for(int i = 0; i < N; i++) c[k] += a[i] * b[(k-i + N)%N];
	return c;
}

vector<long long> cyclic_convolution(vector<long long> &a, vector<long long> &b) { 
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	assert(a.size() == b.size());
	int N = max((int)a.size(), (int)b.size()), n = 1;
	while(n < 2*N) n <<= 1;

	fa.resize(n);
	for(int i = 0; i < (int)a.size(); i++) 
		fa[i + n - a.size()] = fa[i];
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);

	for(int i = 0 ; i < n; i++) 
		fa[i] *= fb[i];

	fft(fa, true);

	vector<long long> c(n);
	for(int i = 0; i < n; i++) c[i] = round(fa[i].real());
	while((int)c.size() > N) c.pop_back();
	return c;
}

template<class T> ostream& operator <<(ostream &os, const vector<T> &v) { for(auto &e: v) os << e << " "; return os; }
 
int main(){
	int N, M; cin >> N >> M;
	vector<long long> A(N), B(M);
	for(auto &e: A) cin >> e;
	for(auto &e: B) cin >> e;
	cout << convolution(A, B) << endl;
}