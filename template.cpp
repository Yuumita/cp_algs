#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T, vector<T>, greater<T>>;
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define forn(i,l,r) for(int i=(l); (i)<(r); i++)
#define rep(i,l,r) for(int i=(l); (i)<(r); i++)
#define rrep(i,l,r) for(int i=(r) - 1; (i) >= (l); i--)
#define fore(i,a) for(auto &i:a)
#define deb(x) cerr<<#x<<" = "<<x<<endl;
const int MOD = 1e9 + 7; // 998244353
const int INF = 2e9 + 7; 
const int MAX = 2e5 + 7;

template<class T> vector<int> argsort(const vector<T> &vec, bool asc=true){
    vector<int> index(vec.size()); iota(index.begin(), index.end(), 0);
    sort(index.begin(), index.end(), [&vec, &asc](int i, int j) { return asc ? (vec[i] < vec[j]):(vec[i] > vec[j]); });
    return index;
}
template<typename T>T min(const vector<T>&v) { return *min_element(v.begin(),v.end());   }
template<typename T>T max(const vector<T>&v) { return *max_element(v.begin(),v.end());   }
template<typename T>T acc(const vector<T>&v) { return accumulate(v.begin(),v.end(),T(0));}
template<class T> bool ckmin(T &a, const T &b) { return b < a ? a = b, true : false; } // a := min(a, b)
template<class T> bool ckmax(T &a, const T &b) { return b > a ? a = b, true : false; } // a := max(a, b)
template<class T> ostream& operator <<(ostream &os, const vector<T> &v) { for(auto &e: v) os << e << " "; return os; }


void solve(){
}
 
int main(){
	// ios_base::sync_with_stdio(0); cin.tie(NULL);
	int t = 1;
	// cin >> t;
	for(int tt=1;tt<=t;tt++){
		//cout <<"Case #" << tt << ": ";
		solve();
		cout << endl;
	}
}