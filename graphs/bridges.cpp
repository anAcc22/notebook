#include "../templates/base_template.hpp"

int n;

int main() {
  cin >> n;

  V adj(n, V());
  vector<ii> bridges;
  vector<int> depth(n), memo(n);

  // NOTE: assumes zero-indexed nodes
  auto solve = [&](auto self, int u, int pu) -> void {
    for (auto &v : adj[u])
      if (v != pu) {
        if (!depth[v]) {
          depth[v] = depth[u] + 1;
          self(self, v, u);
          memo[u] += memo[v];
        } else if (depth[v] < depth[u]) {
          memo[u]++;
        } else {
          memo[u]--;
        }
      }
    if (depth[u] != 1 && !memo[u]) bridges.push_back({ pu, u });
  };

  depth[0] = 1;
  solve(solve, 0, -1);
}
