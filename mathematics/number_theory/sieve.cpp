#include <bits/stdc++.h>
using namespace std;


// O(1) prime check and O(logA) factorization in [1, N]
// with O(N) precomputation

const int MAXN = 2e5;

int spf[MAXN + 1]; // Smallest prime factor

void Sieve() {
    // Initilazation
    for(int i = 1; i <= MAXN; i++) spf[i] = i; 
    for(int i = 2; i <= MAXN; i += 2) spf[i] = 2;
    for(int i = 3; i <= MAXN; i += 2) if(spf[i] == i) {
        // go through all numbers divisible by i and check if it not already marked
        for(long long j = (long long)i*i; j <= MAXN; j += i){
            if(spf[j] == j)
                spf[j] = i;
        }
    }
}

// Returns factorization of x in O(logn)
vector<int> getFactoriazation(int x) {
    vector<int> ret;
    while(x > 1) {
        ret.push_back(spf[x]);
        x /= spf[x];
    }
    return ret;
}


int main(){
    Sieve(); 
}