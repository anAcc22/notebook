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
