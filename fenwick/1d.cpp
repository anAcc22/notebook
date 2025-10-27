#include "../templates/base_template.hpp"

// NOTE: assumes one-indexed queries
template <typename T = int>
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
  void range_add(int l, int r, T addend) {
    point_add(l, addend);
    point_add(r + 1, -addend);
  }
  T point_ask(int i) {
    T sum = {};
    for (; i; i -= lso(i)) sum += tree[i];
    return sum;
  }
  T range_ask(int x, int y) { return point_ask(y) - point_ask(x - 1); }
};
