#include "../templates/base_template.hpp"

struct Point {
  ll x, y;
};

int orientation(Point a, Point b, Point c) {
  ll v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
  if (v < 0) return -1; // clockwise
  if (v > 0) return +1; // counter-clockwise
  return 0;
}

bool cw(Point a, Point b, Point c, bool include_collinear) {
  int o = orientation(a, b, c);
  return o < 0 || (include_collinear && o == 0);
}

bool ccw(Point a, Point b, Point c, bool include_collinear) {
  int o = orientation(a, b, c);
  return o > 0 || (include_collinear && o == 0);
}

// WARN: returns the hull in CLOCKWISE order (affects `a` inplace)
void convex_hull(vector<Point> &a, bool include_collinear = false) {
  if (S(a) == 1) return;

  sort(A(a), [](Point a, Point b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  });

  Point p1 = a[0], p2 = a.back();
  vector<Point> up, down;

  up.P(p1);
  down.P(p1);

  for (int i = 1; i < S(a); i++) {
    if (i == S(a) - 1 || cw(p1, a[i], p2, include_collinear)) {
      while (S(up) >= 2
             && !cw(up[S(up) - 2], up[S(up) - 1], a[i], include_collinear))
        up.pop_back();
      up.P(a[i]);
    }
    if (i == S(a) - 1 || ccw(p1, a[i], p2, include_collinear)) {
      while (S(down) >= 2
             && !ccw(
                 down[S(down) - 2], down[S(down) - 1], a[i], include_collinear))
        down.pop_back();
      down.P(a[i]);
    }
  }

  if (include_collinear && S(up) == S(a)) {
    reverse(A(a));
    return;
  }

  a.clear();

  for (int i = 0; i < S(up); i++) a.P(up[i]);
  for (int i = S(down) - 2; i > 0; i--) a.P(down[i]);
}
