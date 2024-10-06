#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template<typename T = long long>
T exp(T x, long long n) {
    T res = 1;
    while(n > 0) {
        if(n & 1) res *= x;
        x *= x, n >>= 1;
    }
    return res;
}
 
int main(){
    cout << exp(3,3) << endl;
}