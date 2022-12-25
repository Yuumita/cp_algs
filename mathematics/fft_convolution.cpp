#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert){
	int n = a.size();
	if(n == 1) return;
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

vector<long long> multiply(vector<long long> &a, vector<long long> &b) { 
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < a.size() + b.size()) n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);

	for(int i = 0 ; i < n; i++) fa[i] = fa[i] * fb[i];

	fft(fa, true);

	vector<long long> ab(n);
	for(int i = 0; i < n; i++) ab[i] = round(fa[i].real());
	return ab;
}

void output_poly(vector<long long> &a) {
	for(int k = 0; k < a.size(); k++){
		cout << a[k] << "x^" << k << (k + 1 < a.size() ? " + " : "\n");
	}
}
 
int main(){
	int N, M; cin >> N >> M;
	vector<long long> A(N), B(M), C;
	for(int i = 0; i < N; i++) cin >> A[i];
	for(int i = 0; i < M; i++) cin >> B[i];
	C = multiply(A, B);
	for(int i = 0; i < N + M - 1; i++) cout << C[i] << " ";
	cout << endl;
}