#include "../templates/base_template.hpp"

const int SIEVE_SIZE = 1'000'000; // WARN: rmb to tweak
int eulerPhis[SIEVE_SIZE + 1];
void sieve() {
  for (int i = 1; i <= SIEVE_SIZE; i++) eulerPhis[i] = i;
  for (int i = 2; i <= SIEVE_SIZE; i++)
    if (eulerPhis[i] == i)
      for (int j = i; j <= SIEVE_SIZE; j += i) eulerPhis[j] -= eulerPhis[j] / i;
}
