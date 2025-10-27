#include "../templates/base_template.hpp"

template <typename T>
class PersistentTree {
  struct Node {
    Node *l, *r;
    T s;
    Node(T s)
        : l(nullptr)
        , r(nullptr)
        , s(s) {}
    Node(Node *u)
        : l(u->l)
        , r(u->r)
        , s(u->s) {}
    Node(Node *l, Node *r)
        : l(l)
        , r(r)
        , s() { // WARN: depends on `conquer`
      if (!l && r) s = r->s;
      if (l && !r) s = l->s;
      if (l && r) s = conquer(l->s, r->s);
    }
  };
  int n = 0;
  vector<Node *> roots;
  Node *build(const vector<T> &a, int tl, int tr) {
    if (tl == tr) return new Node(a[tl]);
    int tm = (tl + tr) / 2;
    return new Node(build(a, tl, tm), build(a, tm + 1, tr));
  }
  T query(Node *u, int tl, int tr, int l, int r) {
    if (l > r) return {}; // WARN: depends on `conquer`
    if (l == tl && r == tr) return u->s;
    int tm = (tl + tr) / 2;
    T ls   = query(u->l, tl, tm, l, min(r, tm));
    T rs   = query(u->r, tm + 1, tr, max(l, tm + 1), r);
    return conquer(ls, rs);
  }
  Node *update(Node *u, int tl, int tr, int pos, T s) {
    if (tl == tr) return new Node(s);
    int tm = (tl + tr) / 2;
    if (pos <= tm) return new Node(update(u->l, tl, tm, pos, s), u->r);
    else return new Node(u->l, update(u->r, tm + 1, tr, pos, s));
  }

public:
  PersistentTree(vector<T> &a, int root_cnt, int init)
      : roots(root_cnt) {
    n           = ssize(a);
    roots[init] = build(a, 0, n - 1);
  }
  static T conquer(T x, T y) { // WARN: rmb to tweak
    return x + y;
  }
  void update(int root, int pos, T s) {
    roots[root] = update(roots[root], 0, n - 1, pos, s);
  }
  void cpy_root(int src, int dst) { roots[dst] = new Node(roots[src]); }
  T query(int root, int l, int r) { return query(roots[root], 0, n - 1, l, r); }
};

int n, q, qtype, root_cnt = 0, QMAX = 100'000;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  cin >> n;
  V a(n + 1, 0LL);

  G(i, 1, n) cin >> a[i];
  PersistentTree ptree(a, QMAX + 1, root_cnt);

  cin >> q;

  while (q--) {
    cin >> qtype;
    if (qtype == 1) {
      int idx, v;
      cin >> idx >> v, root_cnt++;
      ptree.cpy_root(root_cnt - 1, root_cnt);
      ptree.update(root_cnt, idx, v);
    } else {
      int hist_num, l, r;
      cin >> hist_num >> l >> r;
      cout << ptree.query(hist_num, l, r) << '\n';
    }
  }
  return 0;
}
