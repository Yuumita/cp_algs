#include <bits/stdc++.h>
using namespace std;


// prefix function (pi) is sometimes called failure function (f/fail)
// f(i) gives answer for [0, i), while pi(i) gives answer for [0,i]

struct KMP {

    const char pseudochar = '#';
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    

    template<typename T = string>
    vector<int> prefix_function(const T &s) {
        int n = int(s.size());
        vector<int> pi(n, 0);
        for(int i = 1; i < n; i++) {
            int j = pi[i-1];
            while(j > 0 && s[i] != s[j]) j = pi[j - 1];
            if(s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }


    // IMPORTANT: aut points to 1 more than the pi function
    // Works strictly for strings
    // computes the transition table aut (index of failure function)
    // where the state of the automaton 
    // is the value of the prefix function
    void compute_automaton(string s, vector<vector<int>> &aut) {
        s += pseudochar;
        int n = s.size();
        vector<int> pi = prefix_function(s);
        for(int i = 0; i < n; i++) {
            for(int c = 0; c < 26; c++) {
                if(i > 0 && 'a' + c != s[i])
                    aut[i][c] = aut[pi[i-1]][c];
                else 
                    aut[i][c] = i + (c == s[i]);
            }
        }
    }


    // s: pattern, t: string
    template<typename T = string>
    vector<int> find_matches(const T &s, T t) {
        int n = int(s.size()), m = int(t.size());
        t.push_back(pseudochar);
        for(auto c: s) t.push_back(c);

        vector<int> matches;
        vector<int> pi = prefix_function(t);
        for(int i = n + 1; i < n + m + 1; i++)
            if(pi[i] == n) res.push_back(i)

        return res;
    }

};


int main() {
    return 0;
}