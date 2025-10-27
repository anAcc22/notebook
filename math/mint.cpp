#include "../templates/base_template.hpp"

class Mint {
  constexpr ll mod(ll x) const {
    if (x < 0) x += MOD;
    return x >= MOD ? x % MOD : x;
  }

public:
  static constexpr ll MOD = 1'000'000'007; // WARN: rmb to tweak
  ll v;
  constexpr ll pow(ll p) const {
    if (!p) return 1;
    ll ans = pow(p / 2);
    return mod(p & 1 ? v * mod(ans * ans) : mod(ans * ans));
  }
  constexpr ll i() const { return pow(MOD - 2); }
  constexpr Mint(ll v = 0)
      : v(mod(v)) {}
  constexpr Mint(const Mint &x)
      : v(x.v) {}
  constexpr Mint &operator++() {
    v = mod(v + 1);
    return *this;
  }
  constexpr Mint operator++(int) {
    Mint _ = *this;
    ++(*this);
    return _;
  }
  constexpr Mint &operator--() {
    v = mod(v - 1);
    return *this;
  }
  constexpr Mint operator--(int) {
    Mint _ = *this;
    --(*this);
    return _;
  }
  constexpr Mint &operator=(const Mint &y) {
    v = y.v;
    return *this;
  }
  constexpr Mint &operator+=(const Mint &y) {
    v = mod(v + y.v);
    return *this;
  }
  constexpr Mint &operator-=(const Mint &y) {
    v = mod(v - y.v);
    return *this;
  }
  constexpr Mint &operator*=(const Mint &y) {
    v = mod(v * y.v);
    return *this;
  }
  constexpr Mint &operator/=(const Mint &y) {
    v = mod(v * y.i());
    return *this;
  }
  friend constexpr Mint operator+(Mint x, const Mint &y) {
    x += y;
    return x;
  }
  friend constexpr Mint operator-(Mint x, const Mint &y) {
    x -= y;
    return x;
  }
  friend constexpr Mint operator*(Mint x, const Mint &y) {
    x *= y;
    return x;
  }
  friend constexpr Mint operator/(Mint x, const Mint &y) {
    x /= y;
    return x;
  }
  friend constexpr bool operator==(const Mint &x, const Mint &y) {
    return x.v == y.v;
  }
  friend constexpr bool operator!=(const Mint &x, const Mint &y) {
    return x.v != y.v;
  }
  friend ostream &operator<<(ostream &os, const Mint &x) { return os << x.v; }
};
