#include "../templates/proton_template.hpp"

// Point update range query segtree over arbitrary state
template<typename T>
struct Tree {
    ll n;
    vector<T> v;
    Tree(ll a_n): n(a_n), v(a_n << 2ll, T::identity()) {}
    void _build(ll i, ll l, ll r, const vector<T>& a) {
        if(l == r) {
            v[i] = a[l];
            return;
        }
        ll m = (l + r) >> 1ll;
        _build(i << 1ll, l, m, a);
        _build((i << 1ll) | 1ll, m + 1ll, r, a);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
    }
    void _build(ll i, ll l, ll r, T a_v) {
        if(l == r) {
            v[i] = a_v;
            return;
        }
        ll m = (l + r) >> 1ll;
        _build(i << 1ll, l, m, a_v);
        _build((i << 1ll) | 1ll, m + 1ll, r, a_v);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
    }
    void _build(ll i, ll l, ll r, const function<T(ll)>& init) {
        if(l == r) {
            v[i] = init(l);
            return;
        }
        ll m = (l + r) >> 1ll;
        _build(i << 1ll, l, m, init);
        _build((i << 1ll) | 1ll, m + 1ll, r, init);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
    }
    void build(const vector<T>& a) {
        _build(1ll, 0ll, n - 1ll, a);
    }
    void build(T a_v) {
        _build(1ll, 0ll, n - 1ll, a_v);
    }
    void build(const function<T(ll)>& init) {
        _build(1ll, 0ll, n - 1ll, init);
    }
    T _qry(ll i, ll l, ll r, ll ql, ll qr) {
        if(ql > qr) return T::identity();
        if(ql > r || qr < l) return T::identity();
        if(ql == l && qr == r) return v[i];
        ll m = (l + r) >> 1ll;
        return _qry(i << 1ll, l, m, ql, min(qr, m)) + _qry((i << 1ll) | 1ll, m + 1ll, r, max(ql, m + 1ll), qr);
    }
    T qry(ll ql, ll qr) {
        return _qry(1ll, 0ll, n - 1ll, ql, qr);
    }
    void _upd(ll i, ll l, ll r, ll qi, const T& nv) {
        if(l == r) {
            v[i] = nv;
            return;
        }
        ll m = (l + r) >> 1ll;
        if(qi <= m) _upd(i << 1ll, l, m, qi, nv);
        else _upd((i << 1ll) | 1ll, m + 1ll, r, qi, nv);
        v[i] = v[i << 1ll] + v[(i << 1ll) | 1ll];
    }
    void upd(ll qi, const T& nv) {
        _upd(1ll, 0ll, n - 1ll, qi, nv);
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
        return Mono(min(v, o.v));
    }
    static inline Mono identity() {
        return Mono(INF(ll));
    }
};