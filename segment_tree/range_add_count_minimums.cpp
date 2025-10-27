#include "../templates/base_template.hpp"

class LazyTree {
  struct LazyNode {
    int add_val;
    bool has_add;
    bool has_update() { return has_add; }
  };
  int n;
  vector<LazyNode> lazy;
  vector<ii> a, tree;
  void build(int i, int l, int r) {
    if (l == r) tree[i] = a[l];
    else {
      int m = (l + r) / 2;
      build(2 * i, l, m);
      build(2 * i + 1, m + 1, r);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  void push(int i) {
    tree[2 * i][0] += lazy[i].add_val;
    lazy[2 * i].add_val += lazy[i].add_val;
    lazy[2 * i].has_add = true;
    tree[2 * i + 1][0] += lazy[i].add_val;
    lazy[2 * i + 1].add_val += lazy[i].add_val;
    lazy[2 * i + 1].has_add = true;
    lazy[i].has_add         = false;
    lazy[i].add_val         = {};
  }
  void add(int i, int tl, int tr, int l, int r, int addend) {
    if (l > r) return;
    if (l == tl && r == tr) {
      tree[i][0] += addend;
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
  ii query(int i, int tl, int tr, int l, int r) {
    if (l > r) return { oo, 0 }; // WARN: depends on `conquer`
    if (l == tl && r == tr) return tree[i];
    if (lazy[i].has_update()) push(i);
    int tm = (tl + tr) / 2;
    return conquer(
        query(2 * i, tl, tm, l, min(r, tm)),
        query(2 * i + 1, tm + 1, tr, max(l, tm + 1), r));
  }

public:
  LazyTree(vector<ii> &a)
      : a(a) {
    n = ssize(a);
    lazy.assign(4 * n, {});
    tree.assign(4 * n, {});
    build(1, 0, n - 1);
  }
  ii conquer(ii x, ii y) { // WARN: rmb to tweak
    if (x[0] == y[0]) return { x[0], x[1] + y[1] };
    return min(x, y);
  }
  void add(int l, int r, int addend) { add(1, 0, n - 1, l, r, addend); }
  ii query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
