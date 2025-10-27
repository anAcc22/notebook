#include "../templates/base_template.hpp"

class SuffixArray {
  static constexpr int alphabet = 256;
  static vector<int> sort_cyclic_shifts(const string &s) {
    int n = ssize(s), classes = 1;
    vector<int> p(n), c(n), pn(n), cn(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (s[p[i]] != s[p[i - 1]]) classes++;
      c[p[i]] = classes - 1;
    }
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
    }
    return p;
  }

public:
  static vector<int> build(const string &_) {
    string s      = _ + '$';
    vector<int> a = sort_cyclic_shifts(s);
    a.erase(begin(a));
    return a;
  }
};

int n;
string s;
auto sar = SuffixArray::build(s);

auto compare = [](const string &t, int suf_idx) -> int {
  for (int i = 0; i < min((int)ssize(t), n - suf_idx); i++) {
    if (t[i] < s[suf_idx + i]) return -1;
    if (t[i] > s[suf_idx + i]) return 1;
    if (i == ssize(t) - 1) return 0;
  }
  return 1;
};

auto count_substr = [](const string &t) -> int {
  // WARN: `sar` := suffix array (declared in the outer scope)
  int lo = 0, hi = n - 1, mi, an = -1, na = -1;
  while (lo <= hi) {
    mi = midpoint(lo, hi);
    if (compare(t, sar[mi]) > 0) an = mi, lo = mi + 1;
    else hi = mi - 1;
  }
  lo = 0, hi = n - 1;
  while (lo <= hi) {
    mi = midpoint(lo, hi);
    if (compare(t, sar[mi]) >= 0) na = mi, lo = mi + 1;
    else hi = mi - 1;
  }
  return na - an;
};
