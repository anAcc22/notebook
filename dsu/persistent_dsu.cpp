#include "../templates/base_template.hpp"

struct DSU {
  V<int> size, parent, time_changed; // WARN: assumes `parent` is zero-indexed
  DSU(int n)
      : size(n, 1)
      , parent(n, 0)
      , time_changed(n, 0) {
    iota(A(parent), 0);
  }
  int find(int x, int time) {
    if (parent[x] == x || time_changed[x] > time) return x;
    return find(parent[x], time);
  }
  bool unite(int x, int y, int time) { // WARN: merge `y` into `x`
    x = find(x, time), y = find(y, time);
    if (x == y) return false;
    if (size[x] < size[y]) swap(x, y);
    size[x] += size[y], parent[y] = x, time_changed[y] = time;
    return true;
  }
};
