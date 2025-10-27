#include "../templates/base_template.hpp"

struct Data {
  vector<int> raw;
};
template <typename T = Data>
class MergeSortTree {
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
  int query(int i, int tl, int tr, int l, int r, int x) {
    if (l > r) return {}; // WARN: depends on `conquer`
    if (l == tl && r == tr) {
      int pos = upper_bound(A(tree[i].raw), x) - begin(tree[i].raw);
      return pos;
    }
    int tm   = (tl + tr) / 2;
    int lans = query(2 * i, tl, tm, l, min(r, tm), x);
    int rans = query(2 * i + 1, tm + 1, tr, max(l, tm + 1), r, x);
    return lans + rans;
  }

public:
  MergeSortTree(vector<T> &a)
      : a(a) {
    n = ssize(a);
    tree.assign(4 * n, {});
    build(1, 0, n - 1);
  }
  T conquer(Data x, Data y) { // WARN: rmb to tweak
    Data ans;
    merge(A(x.raw), A(y.raw), back_inserter(ans.raw));
    return ans;
  }
  void update(int pos, T val) { update(1, 0, n - 1, pos, val); }
  int query(int l, int r, int x) { return query(1, 0, n - 1, l, r, x); }
};
