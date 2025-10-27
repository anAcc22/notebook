struct Frac {
  int x, y;
  Frac(int x, int y)
      : x(x)
      , y(y) {}
  bool operator<(Frac other) const { return x * other.y < y * other.x; }
};
