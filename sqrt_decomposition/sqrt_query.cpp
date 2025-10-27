#include "../templates/base_template.hpp"

int block = 250;
V a, b;

// WARN: assumes zero-indexed queries
auto query = [](int l, int r) -> ll {
  ll ans = 0;
  int bl = l / block, br = r / block;
  if (bl == br) return reduce(begin(a) + l, begin(a) + r + 1);
  for (int i = l; i <= (bl + 1) * block - 1; i++) ans += a[i];
  for (int i = bl + 1; i <= br - 1; i++) ans += b[i];
  for (int i = br * block; i <= r; i++) ans += a[i];
  return ans;
};
