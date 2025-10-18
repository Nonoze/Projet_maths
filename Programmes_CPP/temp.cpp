/*
*	Author: Nonoze
*	Created: Thursday 25/09/2025
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

int n;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tt=1;
	// cin >> tt;
	while(tt--) solve();
	// n=2;
	// while (n<=21) {
	// 	// cout << "n = " << n << " :" << endl;
	// 	solve();
	// 	n++;
	// }
	return 0;
}



bool brute(vector<int> &a, int empl, vector<int> &cnts, int cnt, int k) {
	if (k==0) return cnt==n;
	if (n-empl<k) return 0;
	if (brute(a, empl+1, cnts, cnt, k)) return 1;
	for (auto &u: a) cnts[abs(empl-u)]++, cnt+=cnts[abs(empl-u)]==1;
	a.pb(empl);
	if (brute(a, empl+1, cnts, cnt, k)) return 1;
	a.pop_back();
	for (auto &u: a) cnts[abs(empl-u)]--, cnt-=cnts[abs(empl-u)]==0;
	return 0;
}


void solve() {
	read(n);
	const int beg=8;
	int l=3, r=6, ans=n;
	vector<vector<int>> b;
	while (l<=r) {
		int mid=(l+r)/2;
		bool ok=0;
		vector<bool> vec(n+1, 0);
		for (int mask=0; mask<(1LL<<(n-beg)); mask++) if (__builtin_popcount(mask)==mid) {
			vector<int> a(beg); iota(all(a), 0);
			for (int i=0; i<n-beg; i++) {
				if (mask&(1LL<<i)) a.pb(i+beg);
				vec[i]=0;
			}
			a.pb(n);
			for (int i=0; i<sz(a); i++) {
				for (int j=i+1; j<sz(a); j++) vec[a[j]-a[i]]=1;
			}
			ok=1;
			for (int i=1; i<n; i++) {
				if (!vec[i]) { ok=0; break; }
			}
			if (ok) {
				b.pb(a);
				break;
			}
		}
		if (ok) {
			ans=mid;
			r=mid-1;
		} else l=mid+1;
	}
	for (auto &u: b.back()) cout << u << ' ';
	cout << endl << "ans = " << ans+beg+1 << endl << endl;
	// cout << ans+beg+1 << endl;
}