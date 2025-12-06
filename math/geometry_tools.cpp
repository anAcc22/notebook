/*
for each segment, determine which segments have a point that's strictly inside it

then split into two halves: those on the left and those on the right (split by cross product)

sort each half by angle (i.e., by dotprod / length)

dp1 / l1 < dp2 / l2

dp1 * l2 < dp2 * l1

dp1 * dp1 * n2 < dp2 * dp2 * n1

use complementary counting
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef set<ll> sll;
typedef set<int> si;
typedef map<ll, ll> mll;
typedef map<int, int> mi;
typedef vector<bool> vb;
#define pb push_back
#define INF(dt) numeric_limits<dt>::max()
#define NINF(dt) numeric_limits<dt>::min()

template<typename T>
struct Vec2 {
    T x, y;

    Vec2 operator+(const Vec2& o) const {
        return {x + o.x, y + o.y};
    }

    Vec2 operator-(const Vec2& o) const {
        return {x - o.x, y - o.y};
    }

    Vec2 operator*(T o) const {
        return {x * o, y * o};
    }

    Vec2 operator/(T o) const {
        return {x / o, y / o};
    }

    bool operator==(const Vec2& o) const {
        return x == o.x && y == o.y;
    }

    Vec2 operator-() const {
        return {-x, -y};
    }

    T norm() const {
        return x*x + y*y;
    }
};
template <typename T>
using Line = Vec2<T>;

template<typename T>
using vl = vector<Line<T>>;

// Computes the dot product of two vectors
template<typename T>
inline T dot(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

// Computes the "2d cross product" of two vectors
template<typename T>
inline T cross(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x * b.y - a.y * b.x;
}

// Checks if three points are collinear
template<typename T>
inline bool collinear(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c) {
    return cross(b - a, c - a) == (T)(0ll);
}

// Checks if two vectors are collinear
template<typename T>
inline bool collinear(const Vec2<T>& a, const Vec2<T>& b) {
    return cross(a, b) == (T)(0ll);
}

// Checks if point c lies on the line segment spanned by a and b
template<typename T>
inline bool c_in_ab(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c) {
    return collinear(a, b, c) && dot(a - c, b - c) < (T)(0ll);
}

// Checks if v is STRICTLY counterclockwise u
template<typename T>
inline bool is_ccw(const Vec2<T>& u, const Vec2<T>& v) {
    return cross(u, v) > (T)(0ll);
}

// Checks if v is STRICTLY clockwise u
template<typename T>
inline bool is_cw(const Vec2<T>& u, const Vec2<T>& v) {
    return cross(u, v) < (T)(0ll);
}

// From the vantage point of point a, is point v ccw of point u?
template<typename T>
inline bool is_ccw(const Vec2<T>& a, const Vec2<T>& u, const Vec2<T>& v) {
    return is_ccw(u - a, v - a);
}

// Check if two vectors are perpendicular
template<typename T>
inline bool is_perp(const Vec2<T>& a, const Vec2<T>& b) {
    return dot(a, b) == (T)(0ll);
}

// Projects u onto v
Vec2<double> project(const Vec2<double>& u, const Vec2<double>& v) {
    return v * (dot(u, v) / v.norm());
}

// Reflects x across v
Vec2<double> refl(const Vec2<double>& x, const Vec2<double>& v) {
    return v * (dot(x, v) * 2.0 / v.norm()) - x; 
}

// Rotates (and scales) by another vector in such a way that the resultant vector is still a lattice point
// Specifically, rotates x by the direction specified by u (i.e., the angle u makes with the +x-axis) w.r.t. the origin
template<typename T>
Vec2<T> rotscale(const Vec2<T>& x, const Vec2<T>& u) {
    return {u.x * x.x- u.y * x.y, u.y * x.x + u.x * x.y};
}

// Computes the cosine of the angle between two vectors
double vec_cosine(const Vec2<double>& u, const Vec2<double>& v) {
    return dot(u, v) / sqrt(u.norm() * v.norm());
}

// Computes the counterclockwise radian measure spanned from u to v
double angle(const Vec2<double>& u, const Vec2<double>& v) {
    double rawtheta = acos(min(1.0, max(-1.0, vec_cosine(u, v))));

    return rawtheta + (is_cw(u, v) ? M_PI : 0.0);
}

// Computes TWICE the area of a polygon
// Uses the Shoelace Formula
template<typename T>
using Polygon = vector<Vec2<T>>;

ll twice_area(const Polygon<ll>& poly) {
    ll n = poly.size();

    ll ans = 0ll;
    for(ll i = 0ll; i < n - 1ll; i++) {
        ans += poly[i].x * poly[i + 1ll].y - poly[i].y * poly[i + 1ll].x;
    }
    ans += poly[n - 1ll].x * poly[0ll].y - poly[n - 1ll].y * poly[0ll].x;

    return abs(ans);
}

// Computes the number of lattice points from (0, 0) to (x, y)
ll num_lattice_pts_hit(const Vec2<ll>& v) {
    ll avx = abs(v.x), avy = abs(v.y);
    if(avx == 0ll && avy == 0ll) return 1ll;
    return gcd(avx, avy) + 1ll;
}

// Computes the number of points on the boundary of a polygon with integer coordinates
ll num_lattice_pts_hit(const Polygon<ll>& poly) {
    ll n = poly.size();
    ll ans = 0ll;

    for(ll i = 0ll; i < n - 1ll; i ++) {
        ans += num_lattice_pts_hit(poly[i + 1ll] - poly[i]) - 1ll;
    }

    ans += num_lattice_pts_hit(poly[0ll] - poly[n - 1ll]) - 1ll;

    return ans;
}

// Computes the number of points on the interior of a polygon with integer coordinates
// Uses Pick's Theorem: A = i + b / 2 - 1 -> 2 i = 2 A - b + 2
ll num_interior_pts(const Polygon<ll>& poly) {
    ll num_boundary = num_lattice_pts_hit(poly);
    ll twice_a = twice_area(poly);

    return (twice_a - num_boundary + 2ll) >> 1ll;
}

int main() {
    cin.tie(0);cout.tie(0);
    ios_base::sync_with_stdio(false);

    const double EPS = 0.0000001;

    for(ll i = -50ll; i < 50ll; i++) {
        for(ll j = -50ll; j < 50ll; j++) {
            if(i != 0ll || j != 0ll) {
                assert(is_ccw<ll>({i, j}, {-j, i}));
                assert(!is_perp<ll>({i, j}, {-i, -j}));

                assert(is_ccw<ll>({j, i}, {j + i, i + j}, {0ll, i << 1ll}));
            }
            
            // Testing Counterclockwise Checks
            assert(!is_ccw<ll>({i, j}, {j, -i}));
            assert(!is_ccw<ll>({j, i}, {j + i, i + j}, {j << 1ll, 0ll}));

            assert(!is_ccw<ll>({i, j}, {i << 1ll, j << 1ll}));
            assert(!is_ccw<ll>({i, j}, {-i, -j}));

            assert(!is_ccw<ll>({j, i}, {j + i, i + j}, {j-i, i-j}));
            
            // Testing perpendicularity checks
            assert(is_perp<ll>({i, j}, {j, -i}));
            assert(is_perp<ll>({i, j}, {-j, i}));

            // Testing angles
            double id = i, jd = j;
            if(i != 0ll || j != 0ll) {
                assert(abs(angle({id, jd}, {id, jd})) < EPS);
                assert(abs(angle({id, jd}, {id - jd, id + jd}) - M_PI_4) < EPS);
                assert(abs(angle({id, jd}, {-jd, id}) - M_PI_2) < EPS);
                assert(abs(angle({id, jd}, {-id, -jd}) - 2.0 * M_PI_2) < EPS);
                assert(abs(angle({id, jd}, {jd, -id}) - 3.0 * M_PI_2) < EPS);
            }

            // Testing reflections
            Vec2<double> x = {id, jd};
            Vec2<double> x1 = {-id, jd};
            Vec2<double> x2 = {id, -jd};

            assert((refl(x, {0.0, 1.0}) - x1).norm() < EPS);
            assert((refl(x, {1.0, 0.0}) - x2).norm() < EPS);
            if(i != 0ll || j != 0ll) {
                assert((refl(x, {0.0, 1.0}) - x2).norm() >= EPS);
                assert((refl(x, {1.0, 0.0}) - x1).norm() >= EPS);
            }

            // Testing Projections
            assert(abs(project(x, {0.0, 2.0}).y - jd) < EPS);
            assert(abs(project(x, {3.0, 0.0}).x - id) < EPS);

            assert((project(x, {1.0, 2.0}) - project(x, {-2.0, -4.0})).norm() < EPS);
            assert((project(x, {-1.0, 2.0}) - project(x, {2.0, -4.0})).norm() < EPS);

            // Testing rotations and angles
            Vec2<ll> rot90ccw = {-j, i};
            assert(rotscale<ll>({i, j}, {0ll, 1ll}) == rot90ccw);
            assert(rotscale<ll>({i, j}, {0ll, -1ll}) == -rot90ccw);

            // Testing areas
            assert(twice_area({
                {0ll, 0ll},
                {i, 0ll},
                {0ll, j},
            }) == abs(i * j));

            // Testing boundary and interior point counting
            if(i != 0ll && j != 0ll) {
                Polygon<ll> poly = {
                    {0ll, 0ll},
                    {i, 0ll},
                    {i, j},
                    {0ll, j},
                };
                
                ll num_boundary = num_lattice_pts_hit(poly);
                ll num_interior = num_interior_pts(poly);

                assert(num_boundary == ((abs(i) + abs(j)) << 1ll));
                assert(num_interior == (abs(i) - 1ll) * (abs(j) - 1ll));
            }
        }
    }

    cout << "All tests passed! :D" << endl;

    return 0;
}