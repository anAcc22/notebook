#include "../../templates/proton_template.hpp"

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