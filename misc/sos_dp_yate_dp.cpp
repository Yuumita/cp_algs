#include <bits/stdc++.h>
using namespace std;



// given a function f:2^n -> Z
// computes fz(S) = (sum{f(X)}, over all X<=S) where S is a subset of [n]-1 = {0, 1, ... n-1}
void zeta_transform(vector<int> &fz, vector<int> &f) {
    int N = f.size(), n = 0; 
    while((1 << n) < N) n++;
    assert((1 << n) == N);

    fz.resize(N);

    // (fzh[S][j] is the answer over subsets which differ at most in the first j elements of S)
    vector<vector<int>> fzh(N, vector<int>(n+1)); 
    for(int X = 0; X < N; X++) {
        fzh[X][0] = f[X];
        for(int j = 0; j < n; j++) {
            if(X & (1<<j))
                fzh[X][j+1] = fzh[X][j] + fzh[X^(1<<j)][j];
            else
                fzh[X][j+1] = fzh[X][j];
        }
        fz[X] = fzh[X][n];
    }
}

// given a function f:2^n -> Z
// computes fm(S) = (sum{(-1)^(S\X) f(X)}, over all X<=S) where S is a subset of [n]-1 = {0, 1, ... n-1}
void mobius_transform(vector<int> &fm, vector<int> &f) {
    int N = f.size(), n = 0; 
    while((1 << n) < N) n++;
    assert((1 << n) == N);

    fm.resize(N);
    for(int X = 0; X < N; X++) fm[X] = f[X];

    for(int i = 0; i < n; i++) {
        for(int X = 0; X < N; X++) {
            if(X & (1 << i)) 
                fm[X] -= fm[X ^ (1 << i)];
        }
    }
}

int main() {
    int n = 3, N =(1 << 3);
    vector<int> f(N, 0);
    f[0] = 7, f[1] = 4, f[3] = 5, f[6] = 1;

    vector<int> fz, fm;
    zeta_transform(fz, f);
    mobius_transform(fm, fz);

    for(int i = 0; i < fz.size(); i++) {
        cout << "fz("<<i<<") = " << fz[i] << endl;
    }
    for(int i = 0; i < fz.size(); i++) {
        cout << "fm("<<i<<") = " << fm[i] << endl;
    }

    for(int i = 0; i < f.size(); i++) {
        cout << "f("<<i<<") = " << f[i] << endl;
    }
}