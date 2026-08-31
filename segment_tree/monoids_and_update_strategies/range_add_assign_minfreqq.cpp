#include "../../templates/proton_template.hpp"

// Range min with frequency (tested)
struct Mono {
    ll v, cnt;

    Mono(ll a_v, ll a_cnt): v(a_v), cnt(a_cnt) {};

    inline Mono operator+(const Mono& o) const {
        ll nv = INF(ll), ncnt = 0ll;

        if(v > o.v) {
            nv = o.v;
            ncnt = o.cnt;
        } else if(v < o.v) {
            nv = v;
            ncnt = cnt; 
        } else {
            nv = v;
            ncnt = cnt + o.cnt;
        }

        return Mono(nv, ncnt);
    }
    
    static inline Mono identity() {
        return Mono(INF(ll), 0ll);
    }
};

// Increment/assign (tested!)
struct Upd {
    ll k, v;
    bool assgn;
    Upd(ll a_k, ll a_v, bool a_assgn): k(a_k), v(a_v), assgn(a_assgn) {};

    Mono upd(ll l, ll r, const Mono& old) const {
        Mono nv = Mono(old.v, old.cnt);

        nv.v += k;
        if(assgn) {
            nv.v = v;
            nv.cnt = r - l + 1ll;
        }

        return nv;
    }

    Upd operator+(const Upd& o) const {
        ll nk = 0ll, nv = 0ll;
        bool nassgn = false;
        if(o.assgn) {
            nassgn = true;
            nv = o.v;   
        } else if(assgn) {
            nassgn = true;
            nv = v + o.k;
        } else {
            nk = k + o.k;
        }

        return Upd(nk, nv, nassgn);
    }
    
    bool is_identity() const {
        return k == 0ll && !assgn;
    }

    static inline Upd identity() {
        return Upd(0ll, 0ll, false);
    }
};