#include "../templates/base_template.hpp"

const int NMAX = 1'000 * 100; // WARN: rmb to tweak

int trie[NMAX + 1][26], fail[NMAX + 1], stop[NMAX + 1], idx;

void insert(const string &s) {
  int i = 0;
  for (auto &c : s) {
    if (!trie[i][c - 'a']) trie[i][c - 'a'] = ++idx;
    i = trie[i][c - 'a'];
  }
  stop[i] = true;
}
void build() { // NOTE: construct suffix link(s)
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (trie[0][i]) q.push(trie[0][i]);
  while (!empty(q)) {
    int u = q.front();
    q.pop();
    stop[u] |= stop[fail[u]];
    for (int i = 0; i < 26; i++) {
      if (trie[u][i]) {
        fail[trie[u][i]] = trie[fail[u]][i];
        q.push(trie[u][i]);
      } else {
        trie[u][i] = trie[fail[u]][i];
      }
    }
  }
}
bool search(const string &s) {
  int i = 0;
  for (auto &c : s) {
    i = trie[i][c - 'a'];
    if (stop[i]) return true;
  }
  return false;
}
