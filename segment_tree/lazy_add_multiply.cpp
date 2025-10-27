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

template <typename T>
class LazyTree {
  struct LazyNode {
    T multiply_val = Mint(1);
    T add_val;
    bool has_multiply;
    bool has_add;
    bool has_update() { return has_multiply || has_add; }
  };
  int n;
  vector<LazyNode> lazy;
  vector<Mint> s;
  vector<T> a, tree;
  void build(int i, int l, int r) {
    if (l == r) tree[i] = a[l], s[i] = 1;
    else {
      int m = (l + r) / 2;
      build(2 * i, l, m);
      build(2 * i + 1, m + 1, r);
      s[i]    = (r - l + 1);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  void push(int i) {
    if (i >= 4 * n) return;
    if (2 * i < 4 * n) {
      tree[2 * i] *= lazy[i].multiply_val;
      tree[2 * i] += lazy[i].add_val;
      lazy[2 * i].multiply_val *= lazy[i].multiply_val;
      lazy[2 * i].add_val *= lazy[i].multiply_val;
      lazy[2 * i].add_val += lazy[i].add_val;
      lazy[2 * i].has_multiply = lazy[2 * i].has_add = true;
    }
    if (2 * i + 1 < 4 * n) {
      tree[2 * i + 1] *= lazy[i].multiply_val;
      tree[2 * i + 1] += lazy[i].add_val;
      lazy[2 * i + 1].multiply_val *= lazy[i].multiply_val;
      lazy[2 * i + 1].add_val *= lazy[i].multiply_val;
      lazy[2 * i + 1].add_val += lazy[i].add_val;
      lazy[2 * i + 1].has_multiply = lazy[2 * i + 1].has_add = true;
    }
    lazy[i].has_multiply = lazy[i].has_add = false;
    lazy[i].multiply_val = Mint(1), lazy[i].add_val = {};
  }
  void add(int i, int tl, int tr, int l, int r, T addend) {
    if (l > r) return;
    if (l == tl && r == tr) {
      tree[i] += s[i] * addend;
      lazy[i].add_val += addend;
      lazy[i].has_add = true;
    } else {
      if (lazy[i].has_update()) push(i);
      int tm = (tl + tr) / 2;
      add(2 * i, tl, tm, l, min(r, tm), addend);
      add(2 * i + 1, tm + 1, tr, max(l, tm + 1), r, addend);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  void multiply(int i, int tl, int tr, int l, int r, T val) {
    if (l > r) return;
    if (l == tl && r == tr) {
      tree[i] *= val;
      lazy[i].add_val *= val, lazy[i].multiply_val *= val;
      lazy[i].has_multiply = true;
    } else {
      if (lazy[i].has_update()) push(i);
      int tm = (tl + tr) / 2;
      multiply(2 * i, tl, tm, l, min(r, tm), val);
      multiply(2 * i + 1, tm + 1, tr, max(l, tm + 1), r, val);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  T query(int i, int tl, int tr, int l, int r) {
    if (l > r) return {}; // WARN: depends on `conquer`
    if (l == tl && r == tr) return tree[i];
    if (lazy[i].has_update()) push(i);
    int tm = (tl + tr) / 2;
    return conquer(
        query(2 * i, tl, tm, l, min(r, tm)),
        query(2 * i + 1, tm + 1, tr, max(l, tm + 1), r));
  }

public:
  LazyTree(vector<T> &a)
      : a(a) {
    n = ssize(a);
    s.assign(4 * n, 0);
    lazy.assign(4 * n, {});
    tree.assign(4 * n, {});
    build(1, 0, n - 1);
  }
  T conquer(T x, T y) { // WARN: rmb to tweak
    return x + y;
  }
  void add(int l, int r, T addend) { add(1, 0, n - 1, l, r, addend); }
  void multiply(int l, int r, T val) { multiply(1, 0, n - 1, l, r, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
