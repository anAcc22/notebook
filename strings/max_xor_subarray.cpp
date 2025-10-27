#include "../templates/base_template.hpp"

class Trie {
  int max_length;
  int node_cnt;
  vector<int> stop;
  vector<vector<int>> trie;

public:
  Trie(int max_length)
      : max_length(max_length)
      , node_cnt(0)
      , stop(max_length + 1, false)
      , trie(max_length, vector<int>(2)) {}
  void insert(int word) {
    int node = 0;
    for (int i = 30; i >= 0; i--) {
      int b = (word >> i) & 1;
      if (!trie[node][b]) trie[node][b] = ++node_cnt;
      node = trie[node][b];
    }
    stop[node] = true;
  }
  int find(int word) {
    int node = 0, s = 0;
    for (int i = 30; i >= 0; i--) {
      int b = (word >> i) & 1;
      if (trie[node][b ^ 1]) {
        if (b ^ 1) s |= (1 << i);
        node = trie[node][b ^ 1];
      } else {
        if (b) s |= (1 << i);
        node = trie[node][b];
      }
    }
    return s;
  }
};
