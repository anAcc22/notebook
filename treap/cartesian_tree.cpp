#include "../templates/base_template.hpp"

template <typename T>
class CartesianTree {
  struct Node {
    int p, l, r;
    Node(int p = 0, int l = 0, int r = 0)
        : p(p)
        , l(l)
        , r(r) {}
  };

public:
  int root;
  deque<Node> tree;
  CartesianTree(const vector<T> &a)
      : tree(S(a)) {
    for (int i = 1; i <= S(a) - 1; i++) { // WARN: `a` is one-indexed
      tree[i].p = i - 1;
      while (a[i] < a[tree[i].p]) tree[i].p = tree[tree[i].p].p;
      tree[i].l         = tree[tree[i].p].r;
      tree[tree[i].l].p = i;
      tree[tree[i].p].r = i;
    }
    for (int i = 1; i <= S(a) - 1; i++)
      if (tree[i].p == 0) root = i;
  }
};
