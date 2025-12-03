#include "../templates/base_template.hpp"

struct DSU {
  int kidx;
  vector<int> nodes, krep, kweight; // WARN: assumes `nodes` is zero-indexed
  vector<vector<int>> krt;
  DSU(int n, int ops)
      : kidx(n - 1)
      , nodes(n, -1)
      , krep(n + ops, 0)
      , kweight(n + ops, 0)
      , krt(n + ops) {
    iota(A(krep), 0);
  }
  int find(int x) { return nodes[x] < 0 ? x : nodes[x] = find(nodes[x]); }
  int size(int x) { return -nodes[find(x)]; }
  bool unite(int x, int y, int w) { // WARN: merge `y` into `x`
    x = find(x), y = find(y);
    if (x == y) {
      kidx++;
      krt[kidx].P(krep[x]);
      kweight[kidx] = w;
      krep[x]       = kidx;
      return false;
    }
    if (nodes[x] > nodes[y]) swap(x, y);
    nodes[x] += nodes[y], nodes[y] = x;
    kidx++;
    krt[kidx].P(krep[x]);
    krt[kidx].P(krep[y]);
    kweight[kidx] = w;
    krep[x]       = kidx;
    return true;
  }
  void solve(int u, int prev_w = oo) {
    int min_w = min(prev_w, kweight[u]);
    for (auto v : krt[u]) {
      solve(v, min_w);
    }
  }
};
