#include "../templates/base_template.hpp"

V<ll> primes;

ll eulerPhi(ll n) {
  ll ans = n;
  for (int i = 0; i < S(primes) && primes[i] * primes[i] <= n; i++) {
    if (n % primes[i] == 0) ans -= ans / primes[i];
    while (n % primes[i] == 0) n /= primes[i];
  }
  return ans != 1 ? ans - ans / n : ans;
}
