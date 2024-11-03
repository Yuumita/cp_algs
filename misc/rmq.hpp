#include <bits/stdc++.h>
using namespace std;

template<typename T, bool minimum = true>
struct RMQ {
    int n = 0, K = 25; // array size, maximum power of 2
    vector<T> v; // values
    vector<int> log; // logarithm precomputation
    // index of better value (sparse table index)
    vector<vector<int>> spi; 

    RMQ(const vector<T> &v0 = {}) {
        if(int(v0.size()) > 0) init(v0);
    }

    // if v[i] == v[j] returns j
    int better_index(int i, int j) {
        return (minimum ? v[i] < v[j] : v[i] > v[j]) ? i : j;
    }

    void init(const vector<T> &v0) {
        n = v0.size();
        K = max((n == 0 ? -1: 31 - __builtin_clz(n)) + 1, K);

        v.resize(n);
        spi.assign(n, vector<int> (K+1));
        log.resize(n + 1);
        log[1] = 0;
        for(int i = 2; i <= n; i++) log[i] = log[i/2] + 1;

        for(int i = 0; i < n; i++) v[i] = v0[i];
        for(int i = 0; i < n; i++) spi[i][0] = i;
        for(int j = 1; j <= K; j++)
            for(int i = 0; i + (1 << j) - 1 < n; i++) 
                spi[i][j] = better_index(spi[i][j-1], spi[i + (1 << (j-1))][j-1]);
            
    }

    // Returns minarg v[L..R], (ties broken with bigger index)
    int query_index(int L, int R) {
        assert(0 <= L && R < n && L <= R);
        int j = log[R - L + 1];
        return better_index(spi[L][j], spi[R - (1 << j) + 1][j]);
    }

    // Returns min v[L...R]
    T query(int L, int R) {
        return v[query_index(L, R)];
    }

};