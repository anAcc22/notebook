#include "../templates/base_template.hpp"

class LazyTree {
  int n;
  vector<ll> s, lazy, d;
  vector<ll> a, tree;
  ll sum(ll base, ll diff, ll len) {
    return (2 * base + diff * (len - 1)) * len / 2;
  }
  ll conquer(ll x, ll y) { return x + y; } // WARN: rmb to tweak
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
    tree[2 * i] += sum(lazy[i], d[i], s[2 * i]);
    tree[2 * i + 1] += sum(s[2 * i] * d[i] + lazy[i], d[i], s[2 * i + 1]);
    lazy[2 * i] += lazy[i], d[2 * i] += d[i];
    lazy[2 * i + 1] += s[2 * i] * d[i] + lazy[i], d[2 * i + 1] += d[i];
    lazy[i] = d[i] = 0;
  }
  void
  add(int i, int tl, int tr, int l, int r,
      ll base) { // WARN: requires `base` >= 1
    if (l > r) return;
    if (l == tl && r == tr) {
      tree[i] += sum(base, 1, r - l + 1);
      lazy[i] += base;
      d[i]++;
    } else {
      if (lazy[i]) push(i);
      int tm = (tl + tr) / 2, gap = max(0, min(r, tm) - l + 1);
      add(2 * i, tl, tm, l, min(r, tm), base);
      add(2 * i + 1, tm + 1, tr, max(l, tm + 1), r, base + gap);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  ll query(int i, int tl, int tr, int l, int r) {
    if (l > r) return {}; // WARN: depends on `conquer`
    if (l == tl && r == tr) return tree[i];
    if (lazy[i]) push(i);
    int tm = (tl + tr) / 2;
    return conquer(
        query(2 * i, tl, tm, l, min(r, tm)),
        query(2 * i + 1, tm + 1, tr, max(l, tm + 1), r));
  }

public:
  LazyTree(vector<ll> &a)
      : a(a) {
    n = ssize(a);
    s.assign(4 * n, 0);
    lazy.assign(4 * n, {});
    d.assign(4 * n, {});
    tree.assign(4 * n, {});
    build(1, 0, n - 1);
  }
  void add(int l, int r, ll base) { add(1, 0, n - 1, l, r, base); }
  ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
