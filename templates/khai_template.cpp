#include <bits/stdc++.h>
using namespace std;

#define task "a"
#define etr "\n"
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pli pair<long long,int>
#define pll pair<long long, long long>
#define fi first
#define se second
#define bg begin
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define lwb lower_bound
#define upb upper_bound
#define range(x, l, r) x+l, x+1+r
#define all(x) (x).bg(), (x).end()
#define compact(x) x.resize(unique(all(x)) - (x).bg())

template<class U, class V> istream& operator >> (istream& in, pair<U, V>& p)
{
    in >> p.fi >> p.se;
    return in;
}

template<class U, class V> ostream& operator << (ostream& out, pair<U, V> p)
{
    out << "{" << p.fi << ", " << p.se << "}";
    return out;
}

template<class T> ostream& operator << (ostream& out, vector<T>& v)
{
    out << "{";
    for (int i=0; i<v.size(); i++)
    {
        out << v[i];
        if (i < v.size() - 1) out << ", ";
    }

    out << "}";
    return out;
}

struct Timer
{
    chrono::time_point<chrono::_V2::system_clock, chrono::duration<long long, ratio<1, 1000000000>>> timer;

    void start()
    {
        timer = chrono::high_resolution_clock::now();
    }

    Timer()
    {
        start();
    }

    ld elapsed()
    {
        auto cur = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::nanoseconds>(cur - timer).count() / 1e9;
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r, int t=0)
{
    if (t == 0) return uniform_int_distribution<int>(l, r) (rng);
    else if (t > 0) return max(rand(l, r), rand(l, r, t-1));
    else return min(rand(l, r), rand(l, r, t+1));
}

void freop()
{
    freopen(task".inp", "r", stdin);
    freopen(task".out", "w", stdout);
}

const int N = 1e5, M = 2e5, MOD = 1e9 + 7;

void process()
{

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t=1; //cin >> t;
    while (t--) process();
}

