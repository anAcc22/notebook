#include "../templates/base_template.hpp"

int odds = 0, n, m, o1, o2;
V adj(n + 1, set<int>());
V p;

int main() {
  // NOTE: do some pre-processing
  // ...

  if (odds == 1 || odds >= 3) {
    cout << "IMPOSSIBLE" << '\n';
    return 0;
  }

  auto solve = [&](auto self, int u) -> void {
    auto &vs = adj[u];
    while (!empty(vs)) {
      int v = *begin(vs);
      vs.erase(v);
      adj[v].erase(u);
      self(self, v);
    }
    p.push_back(u);
  };
  // WARN: assume one-indexed nodes
  solve(solve, odds == 2 ? o1 : 1);

  if (S(p) != m + 1) {
    cout << "IMPOSSIBLE" << '\n';
    return 0;
  }
  for (int i = 0; i < m + 1; i++) cout << p[i] << " \n"[i == m];
}
