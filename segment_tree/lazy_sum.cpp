#include "../templates/base_template.hpp"

template <typename T>
class LazyTree {
  struct LazyNode {
    T assign_val;
    T add_val;
    bool has_assign;
    bool has_add;
    bool has_update() { return has_assign || has_add; }
  };
  int n;
  vector<LazyNode> lazy;
  vector<ll> s;
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
    if (lazy[i].has_assign) {
      tree[2 * i]         = s[2 * i] * lazy[i].assign_val;
      tree[2 * i + 1]     = s[2 * i + 1] * lazy[i].assign_val;
      lazy[2 * i].add_val = lazy[2 * i + 1].add_val = {};
      lazy[2 * i].has_add = lazy[2 * i + 1].has_add = false;
      lazy[2 * i].assign_val = lazy[2 * i + 1].assign_val = lazy[i].assign_val;
      lazy[2 * i].has_assign = lazy[2 * i + 1].has_assign = true;
    } else {
      if (lazy[2 * i].has_assign) {
        tree[2 * i] += s[2 * i] * lazy[i].add_val;
        lazy[2 * i].assign_val += lazy[i].add_val;
      } else {
        tree[2 * i] += s[2 * i] * lazy[i].add_val;
        lazy[2 * i].add_val += lazy[i].add_val;
        lazy[2 * i].has_add = true;
      }
      if (lazy[2 * i + 1].has_assign) {
        tree[2 * i + 1] += s[2 * i + 1] * lazy[i].add_val;
        lazy[2 * i + 1].assign_val += lazy[i].add_val;
      } else {
        tree[2 * i + 1] += s[2 * i + 1] * lazy[i].add_val;
        lazy[2 * i + 1].add_val += lazy[i].add_val;
        lazy[2 * i + 1].has_add = true;
      }
    }
    lazy[i].has_assign = lazy[i].has_add = false;
    lazy[i].assign_val = lazy[i].add_val = {};
  }
  void add(int i, int tl, int tr, int l, int r, T addend) {
    if (l > r) return;
    if (l == tl && r == tr) {
      if (lazy[i].has_assign) {
        tree[i] += s[i] * addend;
        lazy[i].assign_val += addend;
      } else {
        tree[i] += s[i] * addend;
        lazy[i].add_val += addend;
        lazy[i].has_add = true;
      }
    } else {
      if (lazy[i].has_update()) push(i);
      int tm = (tl + tr) / 2;
      add(2 * i, tl, tm, l, min(r, tm), addend);
      add(2 * i + 1, tm + 1, tr, max(l, tm + 1), r, addend);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  void assign(int i, int tl, int tr, int l, int r, T val) {
    if (l > r) return;
    if (l == tl && r == tr) {
      if (lazy[i].has_add) {
        lazy[i].has_add = false;
        lazy[i].add_val = {};
      }
      tree[i]            = s[i] * val;
      lazy[i].assign_val = val;
      lazy[i].has_assign = true;
    } else {
      if (lazy[i].has_update()) push(i);
      int tm = (tl + tr) / 2;
      assign(2 * i, tl, tm, l, min(r, tm), val);
      assign(2 * i + 1, tm + 1, tr, max(l, tm + 1), r, val);
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
  void assign(int l, int r, T val) { assign(1, 0, n - 1, l, r, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
