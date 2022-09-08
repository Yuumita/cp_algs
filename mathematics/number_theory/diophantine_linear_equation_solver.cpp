#include <bits/stdc++.h>
using namespace std;

// Extended gcd, returns (x, y): ax + by = gcd(a, b)
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long x1, y1;
    long long d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Returns a solution (x, y) to ax + by = c
bool find_any_solution(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    g = ext_gcd(abs(a), abs(b), x0, y0);
    if (c % g) return false;

    x0 *= c/g, y0 *= c/g; 
    if(a < 0) x0 = -x0;
    if(b < 0) y0 = -y0;
    return true;
}

// Returns the first solution, i.e the one with the smallest positive x (and positive y)
bool find_prime_solution(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    if(!find_any_solution(a, b, c, x0, y0, g)) return false;

	long long k = x0*g/b;
	x0 -= k * b/g, y0 += k * a/g;
    if(x0 < 0) x0 += b/g, y0 -= a/g; // floor negative rounding error
	return (x0 >= 0 && y0 >= 0);
}

int main(){
    long long x, y, g;
    find_prime_solution(20,30,50,x,y,g);
}