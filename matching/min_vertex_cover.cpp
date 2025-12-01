#include "../templates/base_template.hpp"

int l_size, r_size;
V<ii> matching, edg;
V<int> lhs, rhs;

int main() {
  set<ii> seen;
  set<ii> matching_set(A(matching));

  map<ii, V<ii>> adj;
  set<int> to_start;
  V<int> min_cover;

  F(i, 0, l_size) to_start.I(i);

  for (auto [u, v] : edg) {
    if (matching_set.C({ u, v })) {
      adj[{ v, 1 }].P({ u, 0 });
      to_start.X(u);
    } else {
      adj[{ u, 0 }].P({ v, 1 });
    }
  }

  auto dfs = [&](auto self, int u, int state) -> void {
    seen.I({ u, state });
    for (auto [v, nstate] : adj[{ u, state }]) {
      if (seen.C({ v, nstate })) continue;
      self(self, v, nstate);
    }
  };

  for (auto u : to_start) {
    if (seen.C({ u, 0 })) continue;
    dfs(dfs, u, 0);
  }

  for (auto [u, v] : matching) {
    if (seen.C({ v, 1 })) {
      min_cover.P(rhs[v]);
    }
    if (!seen.C({ u, 0 })) {
      min_cover.P(lhs[u]);
    }
  }
}
