#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb  push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define forn(i,l,r) for(int i=l; i<r; i++)
const int MOD = 1e9 + 7, INF = 2e9+5, NN = 2e6;
 

vector<int> get_pi(string S) {
	int n = S.size();
	vector<int> pi(n);
	pi[0] = 0;	
	for(int i = 0; i < n; i++){
		int j = pi[i-1];
		while(j > 0 && S[j] != S[i]) 
			j = pi[j-1];
		if(S[j] == S[i]) 
			j++;
		pi[i] = j;
	}
	return pi;
}

int main(){
  string test = "aabbabca"
  vector<int> pi = get_pi(test);
  for(auto ch : pi) cout << ch;
  return 0;
}
