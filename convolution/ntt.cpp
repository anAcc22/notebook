#include "../templates/base_template.hpp"

constexpr ll MOD = 998'244'353, root = 62;
ll modpow(ll b, ll p) {
  if (p == 0) return 1LL;
  ll ans = modpow(b, p / 2);
  ans    = ((__int128)(ans)*ans) % MOD;
  if (p & 1) ans = (ans * b) % MOD;
  return ans;
}

void ntt(vector<ll> &a) {
  int n = ssize(a), L = 31 - __builtin_clz(n);
  static vector<ll> rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = { 1, modpow(root, MOD >> s) };
    for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % MOD;
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? MOD : 0);
        ai += (ai + z >= MOD ? z - MOD : z);
      }
}

vector<ll> conv(const vector<ll> &a, const vector<ll> &b) {
  if (a.empty() || b.empty()) return {};
  int s = ssize(a) + ssize(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = modpow(n, MOD - 2);
  vector<ll> left(a), right(b), out(n);
  left.resize(n), right.resize(n);
  ntt(left), ntt(right);
  for (int i = 0; i < n; i++)
    out[-i & (n - 1)] = (ll)left[i] * right[i] % MOD * inv % MOD;
  ntt(out);
  return { out.begin(), out.begin() + s };
}
