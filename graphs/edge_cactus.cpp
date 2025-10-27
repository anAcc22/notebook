#include "../templates/base_template.hpp"

struct DSU {
  int cmpCnt, cmpMax;
  V<int> nodes; // WARN: assumes `nodes` is zero-indexed
  DSU(int n)
      : cmpCnt(n)
      , cmpMax(1)
      , nodes(n, -1) {}
  int find(int x) { return nodes[x] < 0 ? x : nodes[x] = find(nodes[x]); }
  int size(int x) { return -nodes[find(x)]; }
  bool unite(int x, int y) { // WARN: merge `y` into `x`
    x = find(x), y = find(y);
    if (x == y) return false;
    if (nodes[x] > nodes[y]) swap(x, y);
    nodes[x] += nodes[y], nodes[y] = x;
    cmpCnt--;
    ckmx(cmpMax, -nodes[x]);
    return true;
  }
};

int n, m;

int main() {
  cin >> n >> m;

  V adj(n + 1, V<ii>());
  V<ii> edg;

  F(i, 0, m) {
    int u, v;
    cin >> u >> v;
    adj[u].P({ v, i });
    adj[v].P({ u, i });
    edg.P({ u, v });
  };

  V mnb(n + 1, n + 1), depth(n + 1, 0);
  mnb[n] = n;
  DSU dsu(m);

  auto solve = [&](auto &&self, int u, int pu, int ei) -> ii {
    depth[u] = depth[pu] + 1;
    ii dmn   = { depth[u], ei };
    for (auto [v, en] : adj[u]) {
      if (v == pu) continue;
      if (depth[v]) ckmn(dmn, ii{ depth[v], en });
      else ckmn(dmn, (ii)self(self, v, u, en));
    }
    if (dmn[0] != depth[u]) {
      int en = dmn[1];
      dsu.unite(ei, en);
    }
    return dmn;
  };

  G(i, 1, n) {
    if (depth[i]) continue;
    solve(solve, i, 0, -1);
  }
}
