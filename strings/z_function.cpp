#include "../templates/base_template.hpp"

auto z_function = [](const string &s) -> vector<int> {
  int l = 0, r = 0, n = ssize(s);
  vector<int> z(n);
  for (int i = 1; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
};
