/*
Problem: https://atcoder.jp/contests/dp/tasks/dp_z
Todo: try solving this problem with DnC if possible

dp[i] = min_j (h_j - h_i)^2 + C + dp[j]
dp[i] = C + h_i^2 + min_j h_j^2 + dp[j] - 2 * h_j * h_i
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
#define INF(dtype) numeric_limits<dtype>::max()

// Create a struct for linear functions
// First argument: slope, second argument: y-intercept
struct Line {
    ll m, b;

    ll evaluate(ll x) const {
        return m * x + b;
    }
};

/*
Maintain the minimum line in the li chao tree
*/
class Tree {
    public:
        Tree *lt, *rt;
        ll l, r;
        Line v;

        Tree(ll a_l, ll a_r): lt(nullptr), rt(nullptr), l(a_l), r(a_r), v({0ll, INF(ll)}) {}

        void build() {
            if(l == r) {
                return;
            }

            ll m = (l + r) >> 1ll;

            lt = new Tree(l, m);
            rt = new Tree(m + 1ll, r);

            lt->build();
            rt->build();
        }

        void insert_line(Line nl) {
            ll m = (l + r) >> 1ll;
            bool less_l = nl.evaluate(l) < v.evaluate(l);
            bool less_m = nl.evaluate(m + 1ll) < v.evaluate(m + 1ll);

            /*
            ! TODO why does swap work
            ! and v = nl does not???

            well, if we do v = nl,
            we simply erase v from existence
            we don't want that---we want to consider both

            so nl is considered now
            therefore we instead propagate v downward
            */
            if(less_m) swap(v, nl);

            if(l == r) {
                return;
            } else if(less_l != less_m) {
                lt->insert_line(nl);
            } else {
                rt->insert_line(nl);
            }
        }

        ll evaluate(ll x) {
            if(l == r) {
                return v.evaluate(x);
            }
            ll m = (l + r) >> 1ll;

            if(x <= m) {
                return min(lt->evaluate(x), v.evaluate(x));
            } else {
                return min(rt->evaluate(x), v.evaluate(x));
            }
        }
};

int main() {
    ll n, c;
    cin >> n >> c;
    vll h(n, 0ll);
    for(ll& v : h) cin >> v;

    Tree tr(1ll, 1'000'000ll);
    tr.build();

    tr.insert_line({-2ll * h[0ll], h[0ll] * h[0ll]});

    vll dp(n, 0ll);

    // tr.insert_line({2ll, 0ll});
    // tr.insert_line({1ll, 2ll});
    // tr.insert_line({0ll, 6ll});
    // tr.insert_line({-1ll, 12ll});
    // tr.insert_line({-2ll, 20ll});

    // for(ll x = 0ll; x <= 12ll; x++) {
    //     cout << "x = " << x << ", ans = " << tr.evaluate(x) << endl;
    // }

    for(ll i = 1ll; i < n; i++) {
        dp[i] = c + h[i] * h[i] + tr.evaluate(h[i]);
        tr.insert_line({-2ll * h[i], h[i] * h[i] + dp[i]});
    }
    cout << dp[n - 1ll] << endl;
    return 0;
}