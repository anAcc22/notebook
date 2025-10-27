#include "../templates/base_template.hpp"

ll modmul(ll x, ll y, ll mod) { return ((__int128)x * y) % mod; }

ll modpow(ll b, ll p, ll mod) {
  if (!p) return 1;
  ll ans = modpow(b, p / 2, mod) % mod;
  ans    = modmul(ans, ans, mod);
  if (p & 1) ans = modmul(ans, b, mod);
  return ans;
}

bool is_prime(ll n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ll A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
     s = __builtin_ctzll(n - 1), d = n >> s;
  for (ll a : A) {
    ll p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}

ll rho(ll n) {
  ll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ll x) { return modmul(x, x, n) + i; };
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}

vector<ll> factor(ll n) {
  if (n == 1) return { 1 };
  auto solve = [&](auto self, ll n) -> V<ll> {
    if (n == 1) return {};
    if (is_prime(n)) return { n };
    auto d  = rho(n);
    V<ll> a = self(self, d), b = self(self, n / d), ans;
    for (auto x : a) ans.P(x);
    for (auto y : b) ans.P(y);
    return ans;
  };
  auto ans = solve(solve, n);
  return ans;
}
