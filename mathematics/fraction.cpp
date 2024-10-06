#include <bits/stdc++.h>
using namespace std;

template <class T>
struct fraction {
    T num, den;
    fraction(T num_, T den_) : num(num_), den(den_) {
        if(den < 0) { num = -num, den = -den; }
    } 
    fraction(): fraction(0, 1) {}
    fraction(T num_) : fraction(num_, 1) {}
    operator double() const { return 1.0 * num / den; }
    
    fraction simplify() {
        T g = __gcd(num, den);
        if(den < 0 && g > 0) g = -g;
        return *this = fraction(num / g, den / g);
    }

    fraction& operator+=(const fraction &rhs) { 
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        return *this;
    }
    fraction operator+(fraction x) const { return fraction(*this) += x; }
    fraction& operator++() { return fraction(*this) += fraction(1); }
    fraction operator++(int) { fraction ans(*this); operator++(); return ans; }
    fraction operator-() const { return fraction(0) -= *this; }
    fraction& operator-=(fraction rhs) { 
        num = num * rhs.den - rhs.num * den;
        den *= rhs.den;
        return *this;
    }
    fraction operator-(fraction rhs) const { return fraction(*this) -= rhs; }
    fraction& operator--() { return fraction(*this) -= fraction(1);}
    fraction operator--(int) { fraction ans(*this); operator--(); return ans; }
    fraction& operator*=(fraction rhs) {
        num *= rhs.num;
        den *= rhs.den;
        return *this;
    } 
    fraction operator*(fraction rhs) const { return fraction(*this) *= rhs; }
    fraction& operator/=(fraction rhs) { 
        num *= rhs.den;
        den *= rhs.num;
        if(den < 0) { num = -num, den = -den; }
        return *this;
    }
    fraction operator/(fraction x) const { return fraction(*this) /= x; }
 
    template<class S> fraction operator+(S x) const { return fraction(*this) += x; }
    template<class S> fraction& operator+=(S x) { return operator+=(fraction(x)); }
    template<class S> fraction operator-(S x) const { return fraction(*this) -= x; }
    template<class S> fraction& operator-=(S x) { return operator-=(fraction(x)); }
    template<class S> fraction operator*(S x) const { return fraction(*this) *= x; }
    template<class S> fraction& operator*=(S x) { return operator*=(fraction(x)); }
    template<class S> fraction operator/(S x) const { return fraction(*this) /= x; }
    template<class S> fraction& operator/=(S x) { return operator/=(fraction(x)); }
 
    fraction pow(int n) const {
        fraction ret(1), mul(*this);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul, n /= 2;
        }
        return ret;
    }

    fraction inv() const {
        return fraction(den, num);
    }

    friend bool operator==(const fraction &lhs, const fraction &rhs) 
        { return lhs.num * rhs.den == rhs.num * lhs.den; }
    friend bool operator!=(const fraction &lhs, const fraction &rhs)
        { return lhs.num * rhs.den != rhs.num * lhs.den; }
    friend bool operator<(const fraction &lhs, const fraction &rhs) 
        { return lhs.num * rhs.den < rhs.num * lhs.den; }
    friend bool operator>(const fraction &lhs, const fraction &rhs)
        { return lhs.num * rhs.den > rhs.num * lhs.den; }
    friend bool operator<=(const fraction &lhs, const fraction &rhs)
        { return lhs.num * rhs.den <= rhs.num * lhs.den; } 
    friend bool operator>=(const fraction &lhs, const fraction &rhs)
        { return lhs.num * rhs.den >= rhs.num * lhs.den; }
 
    friend ostream &operator<<(ostream &os, fraction &f) { 
        f.simplify();
        if(f.den == 1) {
            return os << f.num;
        } else {
            return os << f.num << "/" << f.den;
        }
    }
};
 
using frac = fraction<long long>;


int main() {
    frac a(7, 14), b(3, 17), d(1, 5), e(2, 10), c(20, 5);
    cout << (d == e) << endl;
    cout << a << " " << b << " " << c << " " << d << " "<< e << endl;
}