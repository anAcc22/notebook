#include "../templates/base_template.hpp"

// WARN: assumes zero-indxed nodes
class two_sat {
  int n;
  vector<vector<int>> ori, rev;

public:
  two_sat(int n)
      : n(n) {
    ori.assign(2 * n, {});
    rev.assign(2 * n, {});
  }
  void add_clause(int u, bool u_pos, int v, bool v_pos) {
    ori[2 * u + u_pos].push_back(2 * v + (!v_pos));
    ori[2 * v + v_pos].push_back(2 * u + (!u_pos));
    rev[2 * v + (!v_pos)].push_back(2 * u + u_pos);
    rev[2 * u + (!u_pos)].push_back(2 * v + v_pos);
  }
  bool is_satisfiable() {
    int color = 1;
    stack<int> stk;
    vector<int> seen(2 * n), colors(2 * n);
    auto build_stk = [&](auto build_stk, int u) -> void {
      seen[u] = true;
      for (auto &v : ori[u])
        if (!seen[v]) {
          build_stk(build_stk, v);
        }
      stk.push(u);
    };
    for (int u = 0; u < 2 * n; u++)
      if (!seen[u]) build_stk(build_stk, u);
    auto build_scc = [&](auto build_scc, int u) -> void {
      colors[u] = color, seen[u] = true;
      for (auto &v : rev[u])
        if (!colors[v]) {
          build_scc(build_scc, v);
        }
    };
    while (!stk.empty()) {
      int u = stk.top();
      stk.pop();
      if (!colors[u]) {
        build_scc(build_scc, u);
        color++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (colors[2 * i] == colors[2 * i + 1]) return false;
    }
    return true;
  }
};
