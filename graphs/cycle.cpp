#include "../templates/base_template.hpp"

int n;

int main() {
  V seen(n + 1), a(n + 1);

  G(i, 1, n) cin >> a[i];

  // WARN: assumes one-indexed `a`
  for (int i = 1, j, cycs; i <= n; i++) {
    if (seen[i]) continue;
    j = i, cycs = 0;
    set<int> curs;
    deque<int> path;
    do {
      seen[j] = true, curs.insert(j), path.push_back(j);
      j       = a[j];
      if (curs.contains(j)) {
        cycs = j;
        break;
      }
    } while (!seen[j]);
    if (cycs) {
      while (path.front() != cycs) path.pop_front();
    }
  }
}
