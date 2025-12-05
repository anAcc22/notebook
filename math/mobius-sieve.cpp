#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;

// Precomputes the Mobius Function
vll precomp_mobius(ll n) {
    ll MAX = n;
    vb is_sqfree(MAX + 1ll, true);

    for(ll i = 2ll; i * i <= MAX; i++) {
        for(ll k = i * i; k <= MAX; k += i * i) {
            is_sqfree[k] = false;
        }
    }

    vvll facts;
    
    for(ll i = 0ll; i <= MAX; i++) {
        vll factsr;
        facts.push_back(factsr);
    }
    
    for(ll i = 2ll; i <= MAX; i++) {
        if((ll)facts[i].size() == 0ll) {
            // Is a prime
            for(ll k = i; k <= MAX; k += i) {
                facts[k].push_back(i);
            }
        }
    }

    vll mobius(MAX + 1ll, 0ll);

    for(ll i = 1ll; i <= MAX; i++) {
        if(is_sqfree[i]) {
            mobius[i] = (((ll)(facts[i].size()) & 0b1ll) == 0ll ? 1ll : -1ll);
        }
    }

    return mobius;
}

int main() {
    ll MAX = 100ll;
    vll mobius = precomp_mobius(MAX);

    for(ll i = 0ll; i <= MAX; i++) {
        cout << mobius[i] << " ";
    }
    cout << endl;

    return 0;
}