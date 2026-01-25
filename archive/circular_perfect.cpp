/*
*	Author: Nonoze
*	Created: Friday 23/01/2026
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef DEBUG
	#define dbg(...)
#endif

// #define cout cerr << "OUT: "
#define endl '\n'
#define endlfl '\n' << flush
#define quit(x) return (void)(cout << x << endl)

template<typename T> void read(T& x) { cin >> x; }
template<typename T1, typename T2> void read(pair<T1, T2>& p) { read(p.first), read(p.second); }
template<typename T> void read(vector<T>& v) { for (auto& x : v) read(x); }
template<typename T1, typename T2> void read(T1& x, T2& y) { read(x), read(y); }
template<typename T1, typename T2, typename T3> void read(T1& x, T2& y, T3& z) { read(x), read(y), read(z); }
template<typename T1, typename T2, typename T3, typename T4> void read(T1& x, T2& y, T3& z, T4& zz) { read(x), read(y), read(z), read(zz); }
template<typename T> void print(vector<T>& v) { for (auto& x : v) cout << x << ' '; cout << endl; }

#define sz(x) (int)(x.size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define make_unique(v) sort(all(v)), v.erase(unique(all(v)), (v).end())
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define fi first
#define se second
#define cmin(a, b) a = min(a, b)
#define cmax(a, b) a = max(a, b)
#define YES cout << "YES" << endl
#define NO cout << "NO" << endl
#define QYES quit("YES")
#define QNO quit("NO")

#define int long long
#define double long double
const int inf = numeric_limits<int>::max() / 4;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9+7, LOG=20;



void solve();

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tt=1;
	// cin >> tt;
	while(tt--) solve();
	return 0;
}


int fastpow(int a, int b, int mod) {
	int res=1;
	while (b) {
		if (b&1) res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}

int n, k, m;
vector<int> a;

/*

q=2: 1 2 4
q=3: 1 3 2 7
q=4: 1 3 10 2 5
q=5: 1 5 11 2 4 8
q=8: 1 2 4 8 16 5 18 9 10

*/

void solve() {
	int mx; read(mx);
	int q=2;
	for (; q<=mx; q*=2) {
		n=q*q+q+1;
		vector<bool> vis(n+1, false);
		a.resize(q+1); a[0]=1;
		for (int i=1; i<q+1; i++) a[i]=(a[i-1]*2)%n;
		if ((a[q]*2)%n!=1) {
			cout << "Failed for q = " << q << endl;
			continue;
		}
		bool ok=1;
		cout << q << endl;
		for (int i=0; i<q+1; i++) {
			for (int j=0; j<q+1; j++) {
				int val=(a[i]-a[j]+n)%n;
				if (val!=0) {
					if (vis[val]) {
						ok=0;
						cout << val << ' ';
						break;
					}
					vis[val]=1;
				}
			}
		}
		if (ok) {
			cout << "n = " << n << " :" << endl;
		} else cout << endl;
		print(a);
	}
}