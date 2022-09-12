#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template<int MOD, bool is_prime = true>
struct mint {
    int v;
    mint(): v(0) {}
    mint(int vv) : v(vv < 0 ? vv % MOD + MOD : vv % MOD) {}
    mint(int vv, nullptr_t) : v(vv) {}
    explicit operator bool() const { return v; }

    mint &operator += (const mint &p) {
        if((v += p.v) >= MOD) v -= MOD;
        return *this;
    }
    mint &operator -= (const mint &p) {
        if((v += MOD - p.v) >= MOD) v -= MOD;
        return *this;
    }
    mint &operator *= (const mint &p) {
        v = (int)(1ll * v * p.v % MOD);
        return *this;
    }
    mint &operator /= (const mint &p) {
        *this *= p.inverse();
        return *this;
    }

    mint &operator ++ () {
		v = (v == MOD - 1 ? 0 : v + 1);
        return *this;
    }
    mint &operator -- () {
		v = (v == 0 ? MOD - 1 : v - 1);
        return *this;
    }

	mint operator++(int) { mint before = *this; ++*this; return before; }
	mint operator--(int) { mint before = *this; --*this; return before; }

    mint operator-() const { return mint(-v); }
    mint operator+(const mint &p) const { return mint(*this) += p; }
    mint operator-(const mint &p) const { return mint(*this) -= p; }
    mint operator*(const mint &p) const { return mint(*this) *= p; }
    mint operator/(const mint &p) const { return mint(*this) /= p; }
    bool operator==(const mint &p) const { return v == p.v; }
    bool operator!=(const mint &p) const { return v != p.v; }

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
        if(is_prime) return pow(v, MOD - 2);
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
        a = mint<MOD>(t);
        return (is);
    }
    
    int get() const { return v; }
	operator int() const { return v; }
    static constexpr int get_mod() { return MOD; }    
};

int main(){
}