#include "../templates/base_template.hpp"

int n;

int main() {
  V adj(n, V()), cap(n, V(n, 0));

  auto bfs = [&](int s, int t, vector<int> &par) -> int {
    par.assign(ssize(adj), -1), par[s] = -2;
    queue<ii> q;
    q.push({ s, oo });
    while (!empty(q)) {
      auto [u, flow] = q.front();
      q.pop();
      for (auto &v : adj[u]) {
        if (par[v] != -1 || cap[u][v] == 0) continue;
        par[v]       = u;
        int new_flow = min(flow, cap[u][v]);
        if (v == t) return new_flow;
        q.push({ v, new_flow });
      }
    }
    return 0;
  };

  // WARN: you may need to alter `int` to `ll` depending on the max flow
  auto max_flow = [&](int s, int t) -> int {
    int flow = 0, new_flow = 0;
    vector par(ssize(adj), 0);
    while ((new_flow = bfs(s, t, par))) {
      flow += new_flow;
      int u = t;
      while (u != s) {
        int pu = par[u];
        cap[pu][u] -= new_flow, cap[u][pu] += new_flow;
        u = pu;
      }
    }
    return flow;
  };
}
