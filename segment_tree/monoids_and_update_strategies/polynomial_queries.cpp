#include "../../templates/proton_template.hpp"

// Range sum
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

// Increment by linear function
struct Upd {
    ll b, c;
    Upd(ll a_b, ll a_c): b(a_b), c(a_c) {};

    Mono upd(ll l, ll r, const Mono& old) const {
        return Mono(old.v + c * (r - l + 1ll) + b * (((l + r) * (r - l + 1ll)) >> 1ll)); // ! CAREFUL: your application of a lazy update was wrong --- forgot to multiply by (r - l + 1)
    }

    Upd operator+(const Upd& o) const {
        return Upd(b + o.b, c + o.c);
    }
    
    bool is_identity() const {
        return b == 0ll && c == 0ll;
    }

    static inline Upd identity() {
        return Upd(0ll, 0ll);
    }
};