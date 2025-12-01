#include "../templates/base_template.hpp"

int n;

void solve_t() {
  cin >> n;

  vector<set<int>> col(n + 1);
  vector adj(n + 1, vector<int>());
  vector ans(n + 1, 0);
  vector c(n + 1, 0);

  G(u, 1, n) { cin >> c[u]; }

  F(_, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    adj[u].P(v);
    adj[v].P(u);
  }

  // auto merge = [&](set<int> &s, set<int> &t) -> void {
  //     if (S(s) < S(t)) swap(s, t);
  //     for (auto &c : t) s.I(c);
  //     t.clear();
  // };

  auto solve = [&](auto self, int u = 1, int pu = 0) -> set<int> * {
    vector<set<int> *> ptrs;

    for (auto v : adj[u]) {
      if (v == pu) continue;
      ptrs.P(self(self, v, u));
    }

    if (empty(ptrs)) {
      col[u].I(c[u]), ans[u] = 1;
      return &col[u];
    }

    int mxi = 0, mxv = S(*ptrs[0]);

    F(i, 1, S(ptrs)) {
      if (S(*ptrs[i]) > mxv) {
        mxv = S(*ptrs[i]);
        mxi = i;
      }
    }

    F(i, 0, S(ptrs)) {
      if (i == mxi) continue;
      for (auto x : *ptrs[i]) {
        ptrs[mxi]->insert(x);
      }
      ptrs[i]->clear();
    }

    ptrs[mxi]->insert(c[u]);
    ans[u] = S(*ptrs[mxi]);

    return ptrs[mxi];
  };
  solve(solve);

  G(u, 1, n) { cout << ans[u] << N(u, n); }
}
