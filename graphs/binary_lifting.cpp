#include "../templates/base_template.hpp"

int n;

int main() {
  // WARN: assumes zero-indexed nodes
  V adj(n, V());

  auto ceil_log2 = [](int n) -> int {
    int ans = 0, cur = 1;
    while (cur < n) cur *= 2, ans++;
    return ans;
  };

  int tab_height = ceil_log2(n);
  vector depth(n, 0);
  vector tab(n, vector(tab_height + 1, -1));

  auto build_tab = [&](auto self, int u, int pu) -> void {
    tab[u][0] = pu;
    for (auto &v : adj[u])
      if (v != pu) {
        depth[v] = depth[u] + 1;
        self(self, v, u);
      }
  };
  depth[0] = 1;
  build_tab(build_tab, 0, -1);

  for (int k = 1; k <= tab_height; k++) {
    for (int u = 0; u < n; u++) {
      if (tab[u][k - 1] != -1) {
        tab[u][k] = tab[tab[u][k - 1]][k - 1];
      }
    }
  }

  auto get_parent = [&](int u, int k) -> int {
    for (int h = 0; h <= tab_height; h++)
      if ((k >> h) & 1) {
        u = tab[u][h];
        if (u == -1) break;
      }
    return u;
  };

  auto get_lca = [&](auto self, int u, int v) -> int {
    if (depth[u] < depth[v]) return self(v, u);
    u = get_parent(u, depth[u] - depth[v]);
    if (u == v) return u;
    for (int h = tab_height; h >= 0; h--) {
      if (tab[u][h] != tab[v][h]) u = tab[u][h], v = tab[v][h];
    }
    return tab[u][0];
  };

  auto get_dist = [&](auto self, int u, int v) -> int {
    if (depth[u] < depth[v]) return self(v, u);
    int delta = depth[u] - depth[v], ans = delta;
    u = get_parent(u, delta);
    if (u == v) return delta;
    for (int h = tab_height; h >= 0; h--) {
      if (tab[u][h] != tab[v][h]) {
        u = tab[u][h], v = tab[v][h];
        ans += 2 * (1 << h);
      }
    }
    return ans + 2;
  };
}
