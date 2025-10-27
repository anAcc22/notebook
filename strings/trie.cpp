#include "../templates/base_template.hpp"

constexpr int K = 26;

struct Vertex {
  vector<int> nxt;
  bool is_end;
  int cnt;
  Vertex()
      : nxt(K, -1)
      , is_end(false)
      , cnt(0) {}
};

vector<Vertex> trie(1);

void insert(const string &s) {
  int u = 0;
  for (const auto &c : s) {
    int i = c - 'a';
    if (trie[u].nxt[i] == -1) {
      trie[u].nxt[i] = ssize(trie);
      trie.emplace_back();
    }
    u = trie[u].nxt[i];
    trie[u].cnt++;
  }
  trie[u].is_end = true;
}

ll search(const string &s) {
  int u  = 0;
  ll ans = 0;
  for (const auto &c : s) {
    int i = c - 'a';
    if (trie[u].nxt[i] == -1) break;
    u = trie[u].nxt[i];
    ans += trie[u].cnt;
  }
  return ans;
}
