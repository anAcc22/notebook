#include "../templates/base_template.hpp"

template <typename T>
class SparseTable {
  const int K = 25;
  int n;
  vector<vector<T>> st;
  T conquer(T x, T y) { return min(x, y); } // WARN: rmb to tweak
public:
  SparseTable(vector<T> &a)
      : n(S(a))
      , st(K + 1, vector<T>(n)) {
    copy(all(a), begin(st[0]));
    for (int i = 1; i <= K; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        st[i][j] = conquer(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T query(int l, int r) {
    int i = __lg(r - l + 1);
    return conquer(st[i][l], st[i][r - (1 << i) + 1]);
  }
};
