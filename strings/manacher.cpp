#include "../templates/base_template.hpp"

class Manacher {
  deque<int> p;
  deque<int> manacher_odd(string s) {
    int n = ssize(s);
    s     = '{' + s + '}';
    deque<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
      p[i] = max(0, min(r - i, p[l + (r - i)]));
      while (s[i - p[i]] == s[i + p[i]]) p[i]++;
      if (i + p[i] > r) l = i - p[i], r = i + p[i];
    }
    p.pop_front(), p.pop_back();
    return p;
  }

public:
  Manacher(const string &s) {
    string t(1, '|');
    for (auto &c : s) t += c, t += '|';
    auto ans = manacher_odd(t);
    ans.pop_front(), ans.pop_back();
    p = ans;
  }
  int get_len(int i, bool is_odd) {
    // NOTE: center palindrome at `i` and `i+1` if `is_odd` is false
    return is_odd ? 2 * (p[2 * i] / 2 - 1) + 1 : p[2 * i + 1] - 1;
  }
};
