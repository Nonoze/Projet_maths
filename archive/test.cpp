#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct State {
    ll val;
    ll cost;
    unsigned long long mask;
};

void generate_states(ll num, int start, int end, vector<State>& states) {
    // Générer tous les sous-ensembles possibles de divisions par 2^k, k in [start, end]
    int len = end - start + 1;
    int limit = 1 << len;
    vector<ll> powers(len);
    for(int i = 0; i < len; i++) {
        powers[i] = 1LL << (start + i);
    }
    for(int m = 0; m < limit; m++) {
        ll val = num;
        ll cost = 0;
        unsigned long long mask = 0;
        for(int i = 0; i < len; i++) {
            if(m & (1 << i)) {
                val /= powers[i];
                cost += powers[i];
                mask |= powers[i];
            }
        }
        states.push_back({val, cost, mask});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        ll x, y; cin >> x >> y;
        if(x == y) {
            cout << 0 << "\n";
            continue;
        }

        // Générer états pour x sur [1..25] et [26..50]
        vector<State> x1, x2, y1, y2;
        generate_states(x, 1, 25, x1);
        generate_states(x, 26, 50, x2);
        generate_states(y, 1, 25, y1);
        generate_states(y, 26, 50, y2);

        // Pour chaque liste, créer un map val -> vector d'états (cost, mask)
        auto store = [](const vector<State>& states) {
            unordered_map<ll, vector<pair<ll,unsigned long long>>> mp;
            for(const auto& s : states) {
                mp[s.val].push_back({s.cost, s.mask});
            }
            return mp;
        };

        auto mx1 = store(x1);
        auto mx2 = store(x2);
        auto my1 = store(y1);
        auto my2 = store(y2);

        ll best = LLONG_MAX;

        // Fonction helper pour vérifier combinaisons
        auto combine_and_update = [&](ll val) {
            if(mx1.find(val) == mx1.end() || mx2.find(val) == mx2.end() ||
               my1.find(val) == my1.end() || my2.find(val) == my2.end()) return;
            const auto& vx1 = mx1[val];
            const auto& vx2 = mx2[val];
            const auto& vy1 = my1[val];
            const auto& vy2 = my2[val];

            // Parcourir toutes combinaisons possibles
            for(const auto& a : vx1) {
                for(const auto& b : vx2) {
                    if((a.second & b.second) != 0) continue;
                    ll cost_x = a.first + b.first;
                    unsigned long long mask_x = a.second | b.second;

                    for(const auto& c : vy1) {
                        if((mask_x & c.second) != 0) continue;
                        for(const auto& d : vy2) {
                            if((mask_x & d.second) != 0) continue;
                            if((c.second & d.second) != 0) continue;
                            ll cost_y = c.first + d.first;
                            ll total_cost = cost_x + cost_y;
                            if(total_cost < best) best = total_cost;
                        }
                    }
                }
            }
        };

        // Parcours de toutes valeurs possibles dans x1
        for(const auto& [val, _] : mx1) {
            combine_and_update(val);
        }

        cout << best << "\n";
    }

    return 0;
}
