#include "../templates/base_template.hpp"

int tc = 1;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution dist(0, oo);

struct Node {
  string val;
  int pri, sze;
  Node *lp, *rp;
  Node(string val)
      : val(val)
      , pri(dist(gen))
      , sze(1)
      , lp(nullptr)
      , rp(nullptr) {}
};

int size(Node *root) { return root ? root->sze : 0; }

void split(Node *root, Node *&lt, Node *&rt, int idx) {
  if (!root) {
    lt = rt = nullptr;
    return;
  }
  if (size(root->lp) + 1 <= idx) {
    split(root->rp, root->rp, rt, idx - (size(root->lp) + 1));
    lt = root;
  } else {
    split(root->lp, lt, root->lp, idx);
    rt = root;
  }
  root->sze = 1 + size(root->lp) + size(root->rp);
}

void merge(Node *&root, Node *lt, Node *rt) {
  if (!lt || !rt) {
    root = lt ? lt : rt;
    return;
  }
  if (lt->pri > rt->pri) {
    merge(lt->rp, lt->rp, rt);
    root = lt;
  } else {
    merge(rt->lp, lt, rt->lp);
    root = rt;
  }
  root->sze = 1 + size(root->lp) + size(root->rp);
}

void concat(Node *root, vector<string> &ans) {
  if (!root) return;
  concat(root->lp, ans);
  ans.push_back(root->val);
  concat(root->rp, ans);
}

void clean(Node *root) {
  if (!root) return;
  clean(root->lp);
  clean(root->rp);
  delete root;
}

int n, q, find_idx = -1;

void find(Node *root, string &s, int offset) {
  if (!root) return;

  if (root->val == s) {
    int cur = offset;

    if (root->lp) cur += root->lp->sze;
    find_idx = cur;

    return;
  }

  int inc = 1;
  if (root->lp) inc += root->lp->sze;

  find(root->lp, s, offset);
  find(root->rp, s, offset + inc);
}

void solve_t() {
  cin >> n >> q;

  vector<string> a(n);

  F(i, 0, n) cin >> a[i];

  Node *root = new Node(a[0]);

  auto insert = [&](int i, string s) -> void {
    Node *lp, *rp;
    split(root, lp, rp, i);
    Node *n_node = new Node(s);
    merge(lp, lp, n_node);
    merge(lp, lp, rp);
    root = lp;
  };

  auto erase = [&](int i) -> void {
    Node *lp, *rp, *n_lp, *n_rp;

    split(root, lp, rp, i);
    split(rp, n_lp, n_rp, 1);

    V<string> ans;

    merge(lp, lp, n_rp);
    root = lp;
  };

  clean(root);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  // cin >> tc; // WARN: comment out (?)

  while (tc--) {
    solve_t();
  }

  return 0;
}
