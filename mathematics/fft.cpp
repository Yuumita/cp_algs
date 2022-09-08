#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb  push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define forn(i,l,r) for(int (i)=(l); (i)<(r); (i)++)
#define rinc(i,l,r) for(int (i)=(l); (i)<=(r); (i)++)
#define rdec(i,r,l) for(int (i)=(r); (i)>=(l); (i)--)
const int MOD = 1e9 + 7, INF = 2e9+5, NN = 2e6;

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

	double angle = 2 * PI / n * (invert ?  -1 : 1);
	cd w(1), we(cos(angle), sin(angle));
	for(int i = 0; i < n/2; i++, w *= we) {
		a[i]       = a0[i] + w * a1[i];
		a[n/2 + i] = a0[i] - w * a1[i];
		if(invert) {
			a[i] /= 2; 
			a[n/2 + i] /= 2;
		}
	}
}

vector<int> multiply(vector<int> &a, vector<int> &b) { 
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < a.size() + b.size()) n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);

	for(int i = 0 ; i < n; i++) fa[i] = fa[i] * fb[i];

	fft(fa, true);

	vector<int> ab(n);
	for(int i = 0; i < n; i++) ab[i] = round(fa[i].real());
	return ab;
}


void output_poly(vector<int> &a) {
	for(int k = 0; k < a.size(); k++){
		cout << a[k] << "x^" << k << (k + 1 < a.size() ? " + " : "\n");
	}
}
 
int main(){
	vector<int> A = {2, 4, 3};
	vector<int> B = {3, -4, 1, 0, 0};

	cout << "A(x)   = ";
	output_poly(A);

	cout << "B(x)   = ";
	output_poly(B);

	vector<int> AB = multiply(A, B);

	cout << "A*B(x) = ";
	output_poly(AB);
}