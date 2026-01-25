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
int pans;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tt=1;
	// cin >> tt;
	while(tt--) solve();
	return 0;
}


vector<vector<int>> solutions;


bool brute(vector<int> &a, int empl, vector<int> &cnts, int cnt, int k) {
	if (n-empl-1<k || k<0) return 0;
	if (cnt>=n/2) {
		if (!solutions.empty() && sz(solutions.back())>sz(a)) solutions.clear();
		solutions.pb(a);
		return 1;
	}
	if (empl==n) return 0;
	bool toreturn=0;
	if (brute(a, empl+1, cnts, cnt, k)) toreturn = 1;
	for (auto &u: a) {
		assert(empl>u);
		auto val=empl-u;
		cnts[min(val, n-val)]++, cnt+=cnts[min(val, n-val)]==1;
	}
	a.pb(empl);
	if (brute(a, empl+1, cnts, cnt, k-1)) toreturn = 1;
	a.pop_back();
	for (auto &u: a) cnts[min(n-(empl-u), empl-u)]--;
	return toreturn;
}


void solve() {
	read(n);
	int l=1, r=7, ans=n;
	vector<vector<int>> b;
	while (l<=r) {
		int mid=(l+r)/2;
		vector<int> a={0};
		vector<int> cnts(n/2+1);
		if (brute(a, 1, cnts, 0, mid-1)) {
			ans=mid;
			r=mid-1;
		} else l=mid+1;
	}
	cout << ans << endl;
	for (auto &u: solutions) {
		vector<int> v;
		for (int i=1; i<ans; i++) v.pb(u[i]-u[i-1]);
		v.pb(u[0]-u[ans-1]+n);
		vector<int> best=v;
		for (int i=0; i<sz(u); i++) {
			rotate(v.begin(), v.begin()+1, v.end());
			cmin(best, v);
		}
		reverse(all(v));
		for (int i=0; i<sz(u); i++) {
			rotate(v.begin(), v.begin()+1, v.end());
			cmin(best, v);
		}
		u=best;
	}
	make_unique(solutions);
	sort(all(solutions));
	for (auto &res: solutions) {
		for (auto &u: res) cout << u << ' ';
		cout << endl;
	}
}