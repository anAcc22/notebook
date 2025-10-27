#include "../templates/base_template.hpp"

template <typename T>
class SegTree {
  int n;
  vector<T> a, tree;
  void build() {
    for (int i = n - 1; i >= 1; --i) {
      tree[i] = conquer(tree[i << 1], tree[(i << 1) ^ 1]);
    }
  }

public:
  SegTree(vector<T> &a)
      : a(a) {
    n = ssize(a);
    tree.assign(2 * n, {});
    for (int i = 0; i < n; i++) tree[i + n] = a[i];
    build();
  }
  T conquer(T x, T y) { // WARN: rmb to tweak
    return min(x, y);
  }
  void update(int i, T val) {
    for (tree[i += n] = val; i > 1; i >>= 1) {
      tree[i >> 1] = conquer(tree[i], tree[i ^ 1]);
    }
  }
  T query(int l, int r) {
    T ans = numeric_limits<T>::max(); // WARN: depends on `conquer`
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = conquer(ans, tree[l++]);
      if (r & 1) ans = conquer(ans, tree[--r]);
    }
    return ans;
  }
};
