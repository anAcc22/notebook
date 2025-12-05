/*
Computes sum_(1 <= x <= n) Diff(f)(x) g(n / x)

in O(sqrt(n)) time
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll f(ll n) {
    return n;
}

inline ll g(ll n) {
    return n;
}

ll hypertech(ll n) {
    ll x = 1ll;
    ll v = n;
    ll ans = 0ll;

    while(x <= n) {
        ans += g(v) * (f(n / v) - f(n / (v + 1ll)));
        x += n / v - n / (v + 1ll);
        v = n / x;
    }

    return ans;
}

ll naive(ll n) {
    ll ans = 0ll;
    for(ll i = 1ll; i <= n; i++) {
        ans += (f(i) - f(i - 1ll)) * g(n / i);
    }

    return ans;
}

int main() {
    for(ll i = 0ll; i < 1000ll; i++) {
        assert(naive(i) == hypertech(i));
    }

    cout << hypertech(1000000000000ll) << endl;

    return  0;
}