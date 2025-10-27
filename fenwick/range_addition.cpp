#include "../templates/base_template.hpp"

// NOTE: assumes one-indexed queries
template <typename T = ll>
class FenwickTree {
  int n;
  vector<T> tree;

public:
  FenwickTree(int tree_size)
      : n(tree_size) {
    tree.assign(n + 1, {});
  }
  void point_add(int i, T addend) {
    for (; i <= n; i += lso(i)) tree[i] += addend;
  }
  T point_ask(int i) {
    T sum = {};
    for (; i; i -= lso(i)) sum += tree[i];
    return sum;
  }
};
class DoubleFenwick {
  int n;
  FenwickTree<ll> b1, b2;
  ll prefix_sum(int idx) { return b1.point_ask(idx) * idx - b2.point_ask(idx); }

public:
  DoubleFenwick(int n)
      : n(n)
      , b1(n)
      , b2(n) {}
  void range_add(int l, int r, ll x) {
    b1.point_add(l, x);
    b1.point_add(r + 1, -x);
    b2.point_add(l, x * (l - 1));
    b2.point_add(r + 1, -x * r);
  }
  ll range_query(int l, int r) { return prefix_sum(r) - prefix_sum(l - 1); }
};
