#include "../templates/base_template.hpp"

// WARN: assumes zero-indexed `adj`
auto build = [](vector<vector<int>> &adj) -> pair<int, vector<int>> {
  int init = 0, n = S(adj);
  V<int> df(n, 0), du(n, 0), dv(n, 0);

  auto dfs
      = [&](auto &&self, int u, int pu, vector<int> &d, int cur = 0) -> void {
    d[u] = cur;
    for (auto v : adj[u]) {
      if (v == pu) continue;
      self(self, v, u, d, cur + 1);
    }
  };

  dfs(dfs, init, -1, df);
  int dia_u = max_element(A(df)) - begin(df);

  dfs(dfs, dia_u, -1, du);
  int dia_v = max_element(A(du)) - begin(du);

  dfs(dfs, dia_v, -1, dv);
  vector<int> ans(n, 0);

  F(i, 0, n) { ckmx(ans[i], max(du[i], dv[i])); }

  return { *max_element(A(du)), ans };
};
