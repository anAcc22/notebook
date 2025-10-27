#include "../templates/base_template.hpp"

constexpr ll MOD = 1'000'000'007;

template <typename T = ll>
struct Mat2D {
  int n, m;
  vector<vector<T>> g;
  Mat2D(int n, int m, bool identity = false)
      : n(n)
      , m(m)
      , g(n, vector<T>(m)) {
    if (n != m || !identity) return;
    for (int i = 0; i < n; i++) {
      g[i][i] = 1;
    }
  }
  constexpr Mat2D pow(ll p) const {
    if (!p) return Mat2D(this->n, this->m, true);
    Mat2D ans = pow(p / 2);
    return p & 1 ? (*this) * ans * ans : ans * ans;
  }
  constexpr Mat2D &operator*=(const Mat2D &b) {
    assert(this->m == b.n);
    Mat2D c = Mat2D(this->n, b.m);
    for (int i = 0; i < this->n; i++) {
      for (int j = 0; j < b.m; j++) {
        for (int k = 0; k < this->m; k++) {
          c.g[i][j] += this->g[i][k] * b.g[k][j];
          c.g[i][j] %= MOD; // WARN: may not be necessary
        }
      }
    }
    n = c.n, m = c.m, g = c.g;
    return *this;
  }
  friend constexpr Mat2D operator*(Mat2D x, const Mat2D &y) {
    x *= y;
    return x;
  }
};
