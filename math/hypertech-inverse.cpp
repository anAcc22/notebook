/*
Computes M(n / v) (mertens function)

in O(n^(3/4)) time
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef map<ll, ll> mll;
typedef vector<bool> vb;

mll mertens(ll n) {
    ll x = n;
    ll v = 1ll;
    ll ans = 0ll;

    // note: usage of map introduces extra log factors
    // but simplifies the implementation
    mll res;

    while(x > 0ll) {
        v = n / x;
        res[v] = 1ll;
        ll x2 = 1ll, v2 = v;
        x2 += v / v2 - v / (v2 + 1ll);
        v2 = v / x2;
        while(v2 > 0ll) {
            res[v] -= res[v2] * (v / v2 - v / (v2 + 1ll));
            x2 += v / v2 - v / (v2 + 1ll);
            v2 = v / x2;
        }
        x -= n / v - n / (v + 1ll);
    }

    return res;
}

// By default, this computes the number of lattice points visible from the origin
inline ll h(ll n) {
    return n * n;
}

/*
suppose h(n) = sum_(1 <= g <= n) f(n / g)

and h is given

hypertech_inv finds f
*/
ll hypertech_inv(ll n) {
    mll mertensvals = mertens(n);

    ll x = 1ll;
    ll v = n;
    ll ans = 0ll;

    while(x <= n) {
        ans += h(v) * (mertensvals[n / v] - mertensvals[n / (v + 1ll)]);
        x += n / v - n / (v + 1ll);
        v = n / x;
    }

    return ans;
}

/*
! Brute Force Functions. Only for testing
*/
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

ll num_coprime(ll n) {
    ll ans = 0ll;
    for(ll x = 1ll; x <= n; x++) for(ll y = 1ll; y <= n; y++) if(gcd(x, y) == 1ll) ans++;
    return ans;
}

int main() {
    
    vll mertensbrute = precomp_mobius(100ll);
    
    for(ll i = 1ll; i <= 100ll; i++) mertensbrute[i] += mertensbrute[i - 1ll];

    for(ll i = 1ll; i <= 10ll; i++) {
        mll mertensres = mertens(i);
        for(auto [k, v]: mertensres) {
            assert(mertensbrute[k] == v);
        }
    }

    for(ll i = 1ll; i <= 100ll; i++) assert(hypertech_inv(i) == num_coprime(i));
    cout << hypertech_inv(100000000ll) << endl;
    cout << hypertech_inv(1000000000ll) << endl;

    return  0;
}