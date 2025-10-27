#include "../templates/base_template.hpp"

template <typename T>
class Hungarian {
  const T INF = numeric_limits<T>::max();

public:
  T tot = 0;
  vector<int> p, way, ans;
  vector<T> u, v;
  Hungarian(const vector<vector<T>> &a) { // WARN: assumes `a` is one-indexed
    int n = ssize(a) - 1, m = ssize(a[0]) - 1;
    u.assign(n + 1, 0), v.assign(m + 1, 0);
    p.assign(m + 1, 0), way.assign(m + 1, 0), ans.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      p[0]   = i;
      int j0 = 0;
      vector<bool> usd(m + 1);
      vector<T> mnv(m + 1, INF);
      do {
        usd[j0] = true;
        int i0 = p[j0], j1 = 0;
        T dlt = INF;
        for (int j = 1; j <= m; j++) {
          if (!usd[j]) {
            T cur = a[i0][j] - u[i0] - v[j];
            if (cur < mnv[j]) mnv[j] = cur, way[j] = j0;
            if (mnv[j] < dlt) dlt = mnv[j], j1 = j;
          }
        }
        for (int j = 0; j <= m; j++) {
          if (usd[j]) u[p[j]] += dlt, v[j] -= dlt;
          else mnv[j] -= dlt;
        }
        j0 = j1;
      } while (p[j0]);
      do {
        int j1 = way[j0];
        p[j0]  = p[j1];
        j0     = j1;
      } while (j0);
    }
    for (int j = 1; j <= m; j++) {
      ans[p[j]] = j;
    }
    tot = -v[0];
  }
};
