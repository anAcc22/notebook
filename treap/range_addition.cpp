#include "../templates/base_template.hpp"

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution dist(0, INT_MAX);

struct Node {
  int val, pri, add, q; // WARN: rmb to tweak (may not need `q`)
  Node *lp, *rp;
  Node(int val, int q)
      : val(val)
      , pri(dist(gen))
      , add(0)
      , q(q)
      , lp(0)
      , rp(0) {}
};

void push(Node *root) {
  if (!root) return;
  if (root->add) {
    if (root->lp) root->lp->val += root->add, root->lp->add += root->add;
    if (root->rp) root->rp->val += root->add, root->rp->add += root->add;
    root->add = 0;
  }
}

void split(Node *root, Node *&lt, Node *&rt, int x) {
  if (!root) {
    lt = rt = nullptr;
    return;
  }
  push(root), push(lt), push(rt);
  if (root->val <= x) {
    split(root->rp, root->rp, rt, x);
    lt = root;
  } else {
    split(root->lp, lt, root->lp, x);
    rt = root;
  }
}

void merge(Node *&root, Node *lt, Node *rt) {
  push(root), push(lt), push(rt);
  if (!lt || !rt) {
    root = lt ? lt : rt;
    return;
  }
  if (lt->pri >= rt->pri) {
    merge(lt->rp, lt->rp, rt);
    root = lt;
  } else {
    merge(rt->lp, lt, rt->lp);
    root = rt;
  }
}

void range_add(Node *&root, int l, int r, int addend) {
  Node *lt = nullptr, *lm = nullptr, *mt = nullptr, *rt = nullptr;
  split(root, lm, rt, r);
  split(lm, lt, mt, l - 1);
  if (mt) mt->val += addend, mt->add += addend;
  merge(lm, lt, mt);
  merge(root, lm, rt);
}

void insert(Node *&root, int x, int q) {
  push(root);
  Node *lt = nullptr, *rt = nullptr;
  split(root, lt, rt, x);
  merge(lt, lt, new Node(x, q));
  merge(root, lt, rt);
}

void concat(Node *root, vector<ii> &a) {
  if (!root) return;
  push(root);
  concat(root->lp, a);
  a.push_back({ root->q, root->val });
  concat(root->rp, a);
}

void clean(Node *root) {
  if (!root) return;
  clean(root->lp);
  clean(root->rp);
  delete root;
}
