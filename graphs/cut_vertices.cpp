#include "../templates/base_template.hpp"

int n;

int main() {
  cin >> n;

  V adj(n, V());
  vector<int> depth(n), memo(n, INT_MAX), cuts(n, false);

  // NOTE: assumes zero-indexed nodes
  auto solve = [&](auto self, int u, int pu) -> void {
    int children = 0;
    for (auto &v : adj[u])
      if (v != pu) {
        if (!depth[v]) {
          depth[v] = depth[u] + 1;
          self(self, v, u);
          memo[u] = min(memo[u], memo[v]);
          children++;
        } else if (depth[v] < depth[u]) {
          memo[u] = min(memo[u], depth[v]);
        } else {
          memo[v] = min(memo[v], depth[u]);
        }
      }
    if (pu == -1) {
      cuts[u] = (children >= 2);
    } else {
      if (memo[u] >= depth[pu]) cuts[pu] = true;
    }
  };

  depth[0] = 1;
  solve(solve, 0, -1);
}
