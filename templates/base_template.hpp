#include <bits/stdc++.h>

using namespace std;

#define P push_back
#define I insert
#define X extract
#define L lower_bound
#define U upper_bound
#define C count

bool ckmn(auto &x, auto y) { return y < x ? x = y, true : false; }
bool ckmx(auto &x, auto y) { return y > x ? x = y, true : false; };
auto lso(integral auto n) { return n & (-n); }
auto pop(integral auto n) { return popcount((unsigned long long)n); };

#define W(x, y) ((x & y) == y)
#define N(i, n) " \n"[i == n]
#define Z(x, i) (x >> i & 1)
#define F(i, l, r) for (int i = l; i < r; i++)
#define G(i, l, r) for (int i = l; i <= r; i++)
#define H(i, r, l) for (int i = r; i >= l; i--)
#define A(a) (a).begin(), (a).end()
#define R(a) (a).rbegin(), (a).rend()
#define S(a) (int)ssize(a)
#define B(a) (a).begin()
#define E(a) (a).end()
#define T(a) prev(E(a))
#define O(a) sort(A(a)), a.erase(unique(A(a)), E(a))

template <typename T = int>
using V  = vector<T>;
using ll = long long;
using ul = unsigned long long;
using ii = array<int, 2>;

constexpr int oo = 0x3f3f3f3f;
constexpr ll OO  = 0x3f3f3f3f3f3f3f3f;
