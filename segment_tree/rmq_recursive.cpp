#include "../templates/base_template.hpp"

template <typename T>
class SegTree {
  int n;
  vector<T> a, tree;
  void build(int i, int l, int r) {
    if (l == r) tree[i] = a[l];
    else {
      int m = (l + r) / 2;
      build(2 * i, l, m);
      build(2 * i + 1, m + 1, r);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  void update(int i, int tl, int tr, int pos, T val) {
    if (tl == tr) tree[i] = val;
    else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) update(2 * i, tl, tm, pos, val);
      else update(2 * i + 1, tm + 1, tr, pos, val);
      tree[i] = conquer(tree[2 * i], tree[2 * i + 1]);
    }
  }
  T query(int i, int tl, int tr, int l, int r) {
    if (l > r) return numeric_limits<T>::max(); // WARN: depends on `conquer`
    if (l == tl && r == tr) return tree[i];
    int tm = (tl + tr) / 2;
    return conquer(
        query(2 * i, tl, tm, l, min(r, tm)),
        query(2 * i + 1, tm + 1, tr, max(l, tm + 1), r));
  }

public:
  SegTree(vector<T> &a)
      : a(a) {
    n = ssize(a);
    tree.assign(4 * n, {});
    build(1, 0, n - 1);
  }
  T conquer(T x, T y) { // WARN: rmb to tweak
    return min(x, y);
  }
  void update(int pos, T val) { update(1, 0, n - 1, pos, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
