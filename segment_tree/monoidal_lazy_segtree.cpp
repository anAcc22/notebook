#include "../templates/proton_template.hpp"

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

    void _upd_one(ll i, ll l, ll r, ll qi, const T& nv) {
        push(i, l, r);
 
        if(l == r) {
            // lazy[i] = lazy[i] + updfn;
            v[i] = nv;
            return;
        }
        ll m = (l + r) >> 1ll;
 
        if(qi <= m) _upd_one(i << 1ll, l, m, qi, nv);
        else _upd_one((i << 1ll) | 1ll, m + 1ll, r, qi, nv);
 
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
    }
 
    void upd_one(ll qi, const T& nv) {
        _upd_one(1ll, 0ll, n - 1ll, qi, nv);
    }
};


/*
This is the Monoid, the state of the segment tree
Define as many attributes as you want in the constructor
Then, define how to combine to Mono objects. For example,
one could define it as addition, multiplication, string concatenation,
or combining substates in a DnC maximum subarray sum implementation.
! Mono must be a Monoid. That is, it must satisfy:
! (1) Associativity (e.g., (a+b)+c = a+(b+c) for addition)
! (2) Existence of an Identity Element (e.g., 0 + x = x for addition), and
! (3) Closure (e.g., a+b returns another integer if both a,b are integers)
*/
struct Mono {
    ll v;
    Mono(ll a_v): v(a_v) {};
    inline Mono operator+(const Mono& o) const {
        return Mono(v + o.v);
    }
    static inline Mono identity() {
        return Mono(0ll);
    }
};

/*
This is the Lazy Segtree Update Strategy
Define as many attributes as you want in the constructor

Then, upd implements a range update over a single node over [l, r]
Given an old state (of type const Mono&) and the interval [l, r], what would
the new state (of type Mono) be?
*/
struct Upd {
    ll k;
    Upd(ll a_k): k(a_k) {};
    Mono upd(ll l, ll r, const Mono& old) const {
        return Mono(old.v + k * (r - l + 1ll));
    }
    Upd operator+(const Upd& o) const {
        return Upd(k + o.k);
    }
    bool is_identity() const {
        return k == 0ll;
    }
    static inline Upd identity() {
        return Upd(0ll);
    }
};