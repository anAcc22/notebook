#include "../templates/base_template.hpp"

int l_size, r_size, edge_cnt;
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  cin >> l_size >> r_size >> edge_cnt;
  V<ii> edg, matching;

  // WARN: assumes both `u` and `v` are zero-indexed
  for (int i = 0, u, v; i < edge_cnt; i++) {
    cin >> u >> v;
    edg.push_back({ u, v });
  }

  shuffle(A(edg), gen);

  auto hopcroft_karp = [&]() -> void {
    V<int> deg(l_size + 1);
    for (auto &[u, v] : edg) deg[u]++;
    partial_sum(begin(deg), end(deg), begin(deg));
    V<int> g(edge_cnt), lmc(l_size, -1), rmc(r_size, -1), a, p, q(l_size);
    for (auto &[u, v] : edg) g[--deg[u]] = v;
    while (true) {
      a.assign(l_size, -1), p.assign(l_size, -1);
      int t = 0, match = false;
      for (int i = 0; i < l_size; i++) {
        if (lmc[i] == -1) q[t++] = a[i] = p[i] = i;
      }
      for (int i = 0; i < t; i++) {
        int x = q[i];
        if (~lmc[a[x]]) continue;
        for (int j = deg[x]; j < deg[x + 1]; j++) {
          int y = g[j];
          if (rmc[y] == -1) {
            while (~y) {
              rmc[y] = x, swap(lmc[x], y), x = p[x];
            }
            match = true;
            break;
          }
          if (p[rmc[y]] == -1) {
            q[t++] = y = rmc[y], p[y] = x, a[y] = a[x];
          }
        }
      }
      if (!match) break;
    }
    for (int i = 0; i < l_size; i++) {
      if (~lmc[i]) matching.push_back({ i, lmc[i] });
    }
  };
}
