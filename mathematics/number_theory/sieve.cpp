#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;

// --- Sieve of Eratosthenes ---

// O(1) prime check and O(logA) factorization in [1, N] with O(N) precomputation with spf (Smallest prime factor)
int spf[MAXN + 1]; 
void prime_sieve() {
    for(int i = 1; i <= MAXN; i++) spf[i] = i; 
    for(int i = 2; i <= MAXN; i += 2) spf[i] = 2;
    for(int i = 3; i <= MAXN; i += 2) if(spf[i] == i) {
        for(long long j = (long long)i*i; j <= MAXN; j += i){
            if(spf[j] == j)
                spf[j] = i;
        }
    }
}

// Returns factorization of x in O(logn)
vector<int> get_factorization(int x) {
    vector<int> ret;
    while(x > 1) {
        ret.push_back(spf[x]);
        x /= spf[x];
    }
    return ret;
}

// Euler totient sieve (phi precomputation)
int phi[MAXN + 1];
void precompute_phi() {
    for(int i = 1; i <= MAXN; i++) phi[i] = i;
    for(int i = 1; i <= MAXN; i++)
        for(int j = i + i; j <= MAXN; j += i)
            phi[j] -= phi[i];
}


int main(){
    Sieve(); 
}