#include <bits/stdc++.h>
using namespace std;

const bool is_prime = true;
const int MOD = 998244353;
struct mint {
    int v;
    mint(): v(0) {}
    mint(int vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    mint(long long vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    mint(int vv, nullptr_t) : v(vv) {}
    operator int() const { return v; }

    mint& operator+=(mint x) { v += x.v; if(v >= MOD) v -= MOD; return *this; }
    mint& operator++() { if(v == MOD - 1) v = 0; else v++; return *this; }
    mint operator++(int) { mint ans(*this); operator++(); return ans; }
    mint operator-() const { return mint(0) -= *this; }
    mint operator-(mint x) const { return mint(*this) -= x; }
    mint& operator-=(mint x) { if(v < x.v) v += MOD; v -= x.v; return *this; }
    mint& operator--() { if(v == 0) v = MOD - 1; else v--; return *this; }
    mint operator--(int) { mint ans(*this); operator--(); return ans; }
    mint& operator*=(mint x) { v = 1ll * v * x.v % MOD; return *this; }
    mint& operator/=(mint x) { return operator*=(x.inverse()); }

    template<class T> mint operator+(T x) const { return mint(*this) += x; }
    template<class T> mint& operator+=(T x) { return operator+=(mint(x)); }
    template<class T> mint operator-(T x) const { return mint(*this) -= x; }
    template<class T> mint& operator-=(T x) { return operator-=(mint(x)); }
    template<class T> mint operator*(T x) const { return mint(*this) *= x; }
    template<class T> mint& operator*=(T x) { return operator*=(mint(x)); }
    template<class T> mint operator/(T x) const { return mint(*this) /= x; }
    template<class T> mint& operator/=(T x) { return operator/=(mint(x)); }

    mint pow(int n) const {
        mint ret(1), mul(v);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul, n /= 2;
        }
        return ret;
    }
    mint inverse() const {
        // Fermat's Little Theorem
        if(is_prime) return pow(MOD - 2);
        int a = v, b = MOD, u = 1, v = 0, t;
        while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
        }
        return mint(u);
    }

    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.v; }
    friend istream &operator>>(istream &is, mint &a) {
        int t; is >> t;
        a = mint(t);
        return (is);
    }
};

int main(){
}