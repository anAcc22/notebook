#include "../templates/base_template.hpp"

int n;

int main() {
  // WARN: assumes one-indexed nodes
  cin >> n;
  V adj(n + 1, V());

  F(_, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    adj[u].P(v);
    adj[v].P(u);
  }

  V seen(n + 1), subt(n + 1, 0);
  V ancestors(n + 1, V<ii>());

  auto build_subt = [&](auto self, int u, int pu) -> int {
    subt[u] = 1;
    for (auto v : adj[u]) {
      if (v == pu || seen[v]) continue;
      subt[u] += self(self, v, u);
    }
    return subt[u];
  };

  // WARN: returns one centroid only (there might be two)
  auto get_centroid = [&](auto self, int u, int pu, int tree_size) -> int {
    for (auto v : adj[u]) {
      if (v == pu || seen[v]) continue;
      if (2 * subt[v] > tree_size) return self(self, v, u, tree_size);
    }
    return u;
  };

  auto build_ancestor
      = [&](auto self, int u, int pu, int centroid, int cur_d = 1) -> void {
    for (auto v : adj[u]) {
      if (v == pu || seen[v]) continue;
      self(self, v, u, centroid, cur_d + 1);
    }
    ancestors[u].P({ centroid, cur_d });
  };

  auto centroid_decomp = [&](auto self, int init = 1) -> void {
    int centroid
        = get_centroid(get_centroid, init, 0, build_subt(build_subt, init, 0));
    for (auto v : adj[centroid]) {
      if (seen[v]) continue;
      build_ancestor(build_ancestor, v, centroid, centroid);
    }
    seen[centroid] = true;
    for (auto v : adj[centroid]) {
      if (seen[v]) continue;
      self(self, v);
    }
  };
}
