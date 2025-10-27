#include "../templates/base_template.hpp"

// NOTE: assumes one-indexed queries
template <typename T = int>
class FenwickTree {
  int height;
  int width;
  vector<vector<T>> tree;

public:
  FenwickTree(int h, int w)
      : height(h)
      , width(w) {
    tree.assign(height + 1, vector<T>(width + 1));
  }
  T point_ask(int x, int y) {
    T ans = {};
    for (; x; x -= lso(x)) {
      for (int i = y; i; i -= lso(i)) {
        ans += tree[x][i];
      }
    }
    return ans;
  }
  T area_ask(int x1, int y1, int x2, int y2) {
    T ans = point_ask(x2, y2) + point_ask(x1 - 1, y1 - 1);
    ans -= point_ask(x2, y1 - 1) + point_ask(x1 - 1, y2);
    return ans;
  }
  void point_add(int x, int y, T addend) {
    for (; x <= height; x += lso(x)) {
      for (int i = y; i <= width; i += lso(i)) {
        tree[x][i] += addend;
      }
    }
  }
  void area_add(int x1, int y1, int x2, int y2, T addend) {
    point_add(x1, y1, addend);
    point_add(x2 + 1, y2 + 1, addend);
    point_add(x2 + 1, y1, -addend);
    point_add(x1, y2 + 1, -addend);
  }
};
