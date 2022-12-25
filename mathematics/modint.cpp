#include <bits/stdc++.h>
using namespace std;

template <int MOD, bool is_prime = false>
struct modint {
    int v;
    modint(): v(0) {}
    modint(int vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    modint(long long vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    modint(int vv, nullptr_t) : v(vv) {}
    operator int() const { return v; }

    modint& operator+=(modint x) { v += x.v; if(v >= MOD) v -= MOD; return *this; }
    modint& operator++() { if(v == MOD - 1) v = 0; else v++; return *this; }
    modint operator++(int) { modint ans(*this); operator++(); return ans; }
    modint operator-() const { return modint(0) -= *this; }
    modint operator-(modint x) const { return modint(*this) -= x; }
    modint& operator-=(modint x) { if(v < x.v) v += MOD; v -= x.v; return *this; }
    modint& operator--() { if(v == 0) v = MOD - 1; else v--; return *this; }
    modint operator--(int) { modint ans(*this); operator--(); return ans; }
    modint& operator*=(modint x) { v = 1ll * v * x.v % MOD; return *this; }
    modint& operator/=(modint x) { return operator*=(x.inverse()); }

    template<class T> modint operator+(T x) const { return modint(*this) += x; }
    template<class T> modint& operator+=(T x) { return operator+=(modint(x)); }
    template<class T> modint operator-(T x) const { return modint(*this) -= x; }
    template<class T> modint& operator-=(T x) { return operator-=(modint(x)); }
    template<class T> modint operator*(T x) const { return modint(*this) *= x; }
    template<class T> modint& operator*=(T x) { return operator*=(modint(x)); }
    template<class T> modint operator/(T x) const { return modint(*this) /= x; }
    template<class T> modint& operator/=(T x) { return operator/=(modint(x)); }

    modint pow(int n) const {
        modint ret(1), mul(v);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul, n /= 2;
        }
        return ret;
    }
    modint inverse() const {
        // Fermat's Little Theorem
        if(is_prime) return pow(MOD - 2);
        int a = v, b = MOD, u = 1, v = 0, t;
        while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
        }
        return modint(u);
    }

    friend ostream &operator<<(ostream &os, const modint &p) { return os << p.v; }
    friend istream &operator>>(istream &is, modint &a) {
        int t; is >> t;
        a = modint(t);
        return (is);
    }
};

const int MOD = 998244353;
using mint = modint<MOD, true>;

int main(){
}