#include "../templates/base_template.hpp"

int block, q;
V ans;

// WARN: assumes zero-indexed queries
struct Query {
  int i, l, r;
  Query(int i, int l, int r)
      : i(i)
      , l(l)
      , r(r) {}
  friend bool operator<(const Query &qa, const Query &qb) {
    if (qa.l / block == qb.l / block) return qa.r < qb.r;
    return qa.l < qb.l;
  }
};
V<Query> queries;

void solve() {
  auto ins = [&](int i) {};
  auto del = [&](int i) {};

  int cl = 0, cr = -1, cur = 0;

  for (auto [i, l, r] : queries) {
    while (cl > l) ins(--cl);
    while (cr < r) ins(++cr);
    while (cl < l) del(cl++);
    while (cr > r) del(cr--);
    ans[i] = cur;
  }
}
