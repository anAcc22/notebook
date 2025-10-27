#include "../templates/base_template.hpp"

class SuffixArray {
  static constexpr int alphabet = 256;

public:
  static int n;
  static vector<vector<int>> cmat;
  static vector<int> sort_cyclic_shifts(const string &s) {
    n           = ssize(s);
    int classes = 1;
    vector<int> p(n), c(n), pn(n), cn(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (s[p[i]] != s[p[i - 1]]) classes++;
      c[p[i]] = classes - 1;
    }
    cmat.P(c);
    for (int h = 0; (1 << h) < n; h++) {
      for (int i = 0; i < n; i++) {
        pn[i] = p[i] - (1 << h);
        if (pn[i] < 0) pn[i] += n;
      }
      fill(begin(cnt), begin(cnt) + classes, 0);
      for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
      for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
      for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
      cn[p[0]] = 0;
      classes  = 1;
      for (int i = 1; i < n; i++) {
        pair<int, int> cur = { c[p[i]], c[(p[i] + (1 << h)) % n] };
        pair<int, int> prv = { c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n] };
        if (cur != prv) classes++;
        cn[p[i]] = classes - 1;
      }
      c.swap(cn);
      cmat.P(c);
    }
    return p;
  }
  static int get_lcp(int i, int j) { // WARN: doesn't work for `i == j`
    int ans = 0;
    for (int k = __lg(n); k >= 0; k--) {
      if (cmat[k][i % n] == cmat[k][j % n]) {
        ans += (1 << k);
        i += (1 << k);
        j += (1 << k);
      }
    }
    return ans;
  }
  static vector<int> build(const string &_) { // NOTE: call at the start
    string s      = _ + '$';
    vector<int> a = sort_cyclic_shifts(s);
    a.erase(begin(a));
    return a;
  }
};
int SuffixArray::n;
vector<vector<int>> SuffixArray::cmat;
