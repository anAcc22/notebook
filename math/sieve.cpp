#include "../templates/base_template.hpp"

constexpr int SIEVE_SIZE = 1'000'000; // WARN: rmb to tweak
bitset<SIEVE_SIZE + 1> bs;
vector<ll> primes;
void sieve() {
  bs.set();
  bs[0] = bs[1] = false;
  for (ll i = 2; i <= SIEVE_SIZE; i++)
    if (bs[i]) {
      for (ll j = i * i; j <= SIEVE_SIZE; j += i) bs[j] = false;
      primes.push_back(i);
    }
}
