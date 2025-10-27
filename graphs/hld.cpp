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
    return max(x, y);
  }
  void update(int i, T val) {
    for (tree[i += n] = val; i > 1; i >>= 1) {
      tree[i >> 1] = conquer(tree[i], tree[i ^ 1]);
    }
  }
  T query(int l, int r) {
    T ans = numeric_limits<T>::min(); // WARN: depends on `conquer`
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = conquer(ans, tree[l++]);
      if (r & 1) ans = conquer(ans, tree[--r]);
    }
    return ans;
  }
};

int n;
constexpr int NMAX = 100'000;

int main() {
  // WARN: assumes zero-indexed nodes
  V adj(n, V());

  V raw(n), s(n); // NOTE: `s` contains the value in each node
  array<int, NMAX> par{}, depth{}, heavy{}, head{}, pos{};
  fill(A(heavy), -1);
  int cur_pos = 0;

  auto dfs = [&](auto self, int u) -> int {
    int subtree = 1, max_child = 0;
    for (auto &v : adj[u])
      if (par[u] != v) {
        par[v] = u, depth[v] = depth[u] + 1;
        int child = self(self, v);
        if (child > max_child) max_child = child, heavy[u] = v;
      }
    return subtree;
  };
  dfs(dfs, 0);

  auto dc = [&](auto self, int u, int h) -> void {
    head[u] = h, pos[u] = cur_pos, raw[cur_pos] = s[u], cur_pos++;
    if (heavy[u] != -1) self(self, heavy[u], h);
    for (auto &v : adj[u])
      if (par[u] != v && v != heavy[u]) {
        self(self, v, v);
      }
  };
  dc(dc, 0, 0);

  SegTree tree(raw);
  auto query = [&](int u, int v) -> int {
    int ans = numeric_limits<int>::min();
    for (; head[u] != head[v]; v = par[head[v]]) {
      if (depth[head[u]] > depth[head[v]]) swap(u, v);
      ans = tree.conquer(ans, tree.query(pos[head[v]], pos[v]));
    }
    if (depth[u] > depth[v]) swap(u, v);
    return tree.conquer(ans, tree.query(pos[u], pos[v]));
  };
}
