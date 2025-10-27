#include "../templates/base_template.hpp"

class GCD {
  static pair<ll, ll> solve(ll a, ll b) {
    if (b == 0) return { 1, 0 };
    auto [y, x] = solve(b, a % b);
    y -= a / b * x;
    return { x, y };
  }

public:
  static pair<ll, ll> extended_gcd(ll a, ll b) {
    auto [x, y] = solve(a, b);
    if (x * a + b * y == -gcd(a, b)) x *= -1, y *= -1;
    return { x, y };
  }
};
