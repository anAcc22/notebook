#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef set<ll> sll;
typedef set<int> si;
typedef map<ll, ll> mll;
typedef map<int, int> mi;
typedef vector<bool> vb;
#define pb push_back
#define INF(dt) numeric_limits<dt>::max()
#define NINF(dt) numeric_limits<dt>::min()

// Range update range query segtree over arbitrary state
template<typename T, typename U>
struct Tree {
    ll n;
    vector<T> v;
    vector<U> lazy;
    Tree(ll a_n): n(a_n), v(a_n << 2ll, T::identity()), lazy(a_n << 2ll, U::identity()) {}
    void _build(ll i, ll l, ll r, const vector<T>& a) {
        if(l == r) {
            v[i] = a[l];
            lazy[i] = U::identity();
            return;
        }
        ll m = (l + r) >> 1ll;
        _build(i << 1ll, l, m, a);
        _build((i << 1ll) | 1ll, m + 1ll, r, a);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
        lazy[i] = U::identity();
    }
    void _build(ll i, ll l, ll r, const T& a_v) {
        if(l == r) {
            v[i] = a_v;
            lazy[i] = U::identity();
            return;
        }
        ll m = (l + r) >> 1ll;
        _build(i << 1ll, l, m, a_v);
        _build((i << 1ll) | 1ll, m + 1ll, r, a_v);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
        lazy[i] = U::identity();
    }
    void _build(ll i, ll l, ll r, const function<T(ll)>& init) {
        if(l == r) {
            v[i] = init(l);
            lazy[i] = U::identity();
            return;
        }
        ll m = (l + r) >> 1ll;
        _build(i << 1ll, l, m, init);
        _build((i << 1ll) | 1ll, m + 1ll, r, init);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
        lazy[i] = U::identity();
    }
    void build(const vector<T>& a) {
        _build(1ll, 0ll, n - 1ll, a);
    }
    void build(const T& a_v) {
        _build(1ll, 0ll, n - 1ll, a_v);
    }
    void build(const function<T(ll)>& init) {
        _build(1ll, 0ll, n - 1ll, init);
    }
    void push(ll i, ll l, ll r) {
        if(lazy[i].is_identity()) {
            return;
        }
        if(l == r) {
            lazy[i] = U::identity();
            return;
        }
        ll m = (l + r) >> 1ll;
        lazy[(i << 1ll)] = lazy[(i << 1ll)] + lazy[i];
        v[(i << 1ll)] = lazy[i].upd(l, m, v[(i << 1ll)]);
        lazy[(i << 1ll) | 1ll] = lazy[(i << 1ll) | 1ll] + lazy[i];
        v[(i << 1ll) | 1ll] = lazy[i].upd(m + 1ll, r, v[(i << 1ll) | 1ll]);
        v[i] = v[(i << 1ll)] + v[(i << 1ll) | 1ll];
        lazy[i] = U::identity();
    }
    T _qry(ll i, ll l, ll r, ll ql, ll qr) {
        if(ql > r || qr < l) return T::identity();
        push(i, l, r);
        if(ql == l && qr == r) return v[i];
        ll m = (l + r) >> 1ll;
        T res = _qry(i << 1ll, l, m, ql, min(qr, m)) + _qry((i << 1ll) | 1ll, m + 1ll, r, max(ql, m + 1ll), qr);
        v[i] = v[(i << 1ll)] + v[(i << 1ll) | 1ll];
        return res;
    }
    T qry(ll ql, ll qr) {
        return _qry(1ll, 0ll, n - 1ll, ql, qr);
    }
    void _upd(ll i, ll l, ll r, ll ql, ll qr, const U& updfn) {
        if(ql > r || qr < l) return;
        push(i, l, r);
        if(ql == l && qr == r) {
            lazy[i] = lazy[i] + updfn;
            v[i] = updfn.upd(l, r, v[i]);
            return;
        }
        ll m = (l + r) >> 1ll;
        _upd(i << 1ll, l, m, ql, min(m, qr), updfn);
        _upd((i << 1ll) | 1ll, m + 1ll, r, max(ql, m + 1ll), qr, updfn);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
    }
    void upd(ll ql, ll qr, const U& updfn) {
        _upd(1ll, 0ll, n - 1ll, ql, qr, updfn);
    }
};

ll md; // ! UPDATE THIS FIELD DURING RUNTIME
// Range sum (modular)
struct Mono {
    ll v;

    Mono(ll a_v): v(a_v) {};

    inline Mono operator+(const Mono& o) const {
        ll nv = v;
        nv += o.v;
        if(nv >= md) nv-=md;
        return Mono(nv);
    }
    
    static inline Mono identity() {
        return Mono(0ll);
    }
};

// Range add/multiply (modular) (tested!)
// ! be careful: this assumes that the multiplier is nonnegative
struct Upd {
    ll add, mult;
    Upd(ll a_add, ll a_mult): add((a_add % md + md) % md), mult(a_mult % md) {};

    Mono upd(ll l, ll r, const Mono& old) const {
        Mono nv = Mono(old.v);
        
        nv.v *= mult;
        nv.v %= md;

        nv.v += (add * (r - l + 1ll)) % md;
        if(nv.v >= md) nv.v -= md;


        return nv;
    }

    Upd operator+(const Upd& o) const {
        /*
        x -> mx + a -> m2(mx + a) + a2
        = (m2 * m)(x) + (m2 a + a2)
        */

        return Upd((o.mult * add + o.add), (o.mult * mult));
    }
    
    bool is_identity() const {
        return add == 0ll && mult == 1ll % md;
    }

    static inline Upd identity() {
        return Upd(0ll, 1ll);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    ll n, q, a_md;
    cin >> n >> q >> a_md;

    md = a_md;

    Tree<Mono, Upd> tr(n);

    vector<Mono> a;
    for(ll i = 0ll; i < n; i++) {
        ll v;
        cin >> v;

        a.push_back(Mono(v % md));
    }

    
    tr.build(a);
    
    
    while(q--) {
        ll qt;
        cin >> qt;
        
        if(qt == 1ll) {
            // range multiply
            ll a, b, x;
            cin >> a >> b >> x;
            a--; b--;
            tr.upd(a, b, Upd(0ll, x));
        } else if(qt == 2ll) {
            ll a, b, x;
            cin >> a >> b >> x;
            a--; b--;
            tr.upd(a, b, Upd(x, 1ll));
        } else {
            // query sum
            ll a, b;
            cin >> a >> b;
            a--; b--;

            std::cout << tr.qry(a, b).v << "\n";
        }
    }
    std::cout << flush;

    return 0;
}