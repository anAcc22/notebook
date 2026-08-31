#include "../../templates/proton_template.hpp"

// Range sum (tested!)
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

// Increment/assign (tested!)
struct Upd {
    ll k, v;
    bool assgn;
    Upd(ll a_k, ll a_v, bool a_assgn): k(a_k), v(a_v), assgn(a_assgn) {};

    Mono upd(ll l, ll r, const Mono& old) const {
        Mono nv = Mono(old.v);

        nv.v += k * (r - l + 1ll);
        if(assgn) {
            nv.v = v * (r - l + 1ll);
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