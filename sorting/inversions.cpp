#include "../templates/base_template.hpp"

auto merge = [](auto self, V<int> &v, int lb, int rb) -> ll {
  if (lb == rb) return 0;
  int mb = (lb + rb) / 2, lp = lb, rp = mb + 1;
  ll ans = self(self, v, lb, mb) + self(self, v, mb + 1, rb);
  while (lp <= mb && rp <= rb) {
    if (v[lp] <= v[rp]) lp++;
    else ans += mb - lp + 1, rp++;
  }
  inplace_merge(B(v) + lb, B(v) + mb + 1, B(v) + rb + 1);
  return ans;
};
