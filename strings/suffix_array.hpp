#include <bits/stdc++.h>
using namespace std;

/// @brief Suffix Array in O(nlogn)
class SuffixArray {
private:
    int N;
    vector<int> sa;
    string &s;
public:
    SuffixArray(string &_s): N(_s.size()), s(_s) {
        s.push_back(0), N++; // insert extra character
        sa.resize(N);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int i, int j) { return s[i] == s[j] ? i > j : s[i] < s[j]; });

        vector<int> c(N);
        c[sa[0]] = 0;
        int C = 1;
        for(int i = 1; i < N; i++)
            c[sa[i]] = (s[sa[i]] == s[sa[i-1]] ? C - 1 : C++);
        
        vector<int> san(N), cn(N), cnt;
        for(int l = 1; l < N; l <<= 1) {
            for(int i = 0; i < N; i++) {
                san[i] = sa[i] - l;
                if(san[i] < 0) san[i] += N;
            }

            cnt.assign(C, 0);
            for(int i = 0; i < N; i++) cnt[c[san[i]]]++;
            for(int j = 1; j < C; j++) cnt[j] += cnt[j-1];
            for(int i = N-1; i >= 0; i--) sa[--cnt[c[san[i]]]] = san[i];

            cn[sa[0]] = 0, C = 1;
            for(int i = 1; i < N; i++) {
                pair<int, int> lhs = {c[sa[i-1]], c[(sa[i-1] + l) % N]};
                pair<int, int> rhs = {c[sa[i]], c[(sa[i] + l) % N]};
                cn[sa[i]] = (lhs == rhs ? C - 1 : C++);
            }
            swap(c, cn);
        }
        s.pop_back(), N--; // remove extra character
        sa.erase(sa.begin());
    }

    vector<int> &get_suffix_array() { return sa; }
    int operator[](int k) const { return sa[k]; }
};