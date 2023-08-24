#define LOCAL
#include <bits/stdc++.h>
const int N = 1e6 + 7;
const int P = 998244353;
const long long INF = 1e16;
#define ll long long
#define ull unsigned long long
#define lll __int128

inline ll mul(ll a, ll b, const ll M)
{
    ll d = a * (long double)b / M;
    ll ret = a * b - d * M;
    if (ret < 0)
        ret += M;
    if (ret >= M)
        ret -= M;
    return ret;
}

inline ll plus2(ll a, ll b, const ll M)
{
    ll d = (a + (long double)b) / M + 0.5;
    ll ret = a + b - d * M;
    if (ret < 0)
        ret += M;
    return ret;
}

inline ll plus(const lll a, const lll b, const lll M)
{
    lll c = a + b;
    if (c >= M)
        return c - M;
    else
        return c;
}

ll Pow(ll x, ll k, const ll M)
{
    ll ret = 1;
    for (; k; x = mul(x, x, M), k >>= 1)
        if (k & 1)
            ret = mul(ret, x, M);
    return ret;
}

ll gcd(ll a, ll b)
{
    while (b)
        b ^= a ^= b ^= a %= b;
    return a;
}
inline ll Abs(ll x) { return (x < 0) ? -x : x; }
static std::mt19937 engine;
bool mr(ll p)
{
    if (p < 2)
        return 0;
    if (p == 2)
        return 1;
    if (p == 3)
        return 1;
    std::uniform_int_distribution<ll> Rand(2, p - 2);
    ll d = p - 1, r = 0;
    while (!(d & 1))
        ++r, d >>= 1;
    for (ll k = 0; k < 10; ++k)
    {
        ll a = Rand(engine);
        ll x = Pow(a, d, p);
        if (x == 1 || x == p - 1)
            continue;
        for (int i = 0; i < r - 1; ++i)
        {
            x = mul(x, x, p);
            if (x == p - 1)
                break;
        }
        if (x != p - 1)
            return 0;
    }
    return 1;
}

using std::min;
inline ll getnext(ll x, ll c, ll n) { return plus(mul(x, x, n), -c, n); }

ll pr(ll n)
{
    if (n == 4)
        return 2;
    std::uniform_int_distribution<ll> Rand(3, n - 1);
    ll x = Rand(engine), y = x;
    ll c = Rand(engine);
    ll d = 1;
    x = getnext(x, c, n);
    y = getnext(y, c, n), y = getnext(y, c, n);
    for (int lim = 1; x != y; lim = min(128, lim << 1))
    {
        ll cnt = 1;
        for (int i = 0; i < lim; ++i)
        {
            ll tmp = mul(cnt, Abs(plus(x, -y, n)), n);
            if (!tmp)
                break;
            cnt = tmp;
            x = getnext(x, c, n);
            y = getnext(y, c, n), y = getnext(y, c, n);
        }
        d = gcd(cnt, n);
        if (d != 1)
            return d;
    }
    return n;
}

ll mxp;
inline void push(ll p)
{
    if (p > mxp)
        mxp = p;
}
void dfs(ll n)
{
    srand(time(0));
    ll d = pr(n), d2;
    while (d == n)
        d = pr(n);
    d2 = n / d;
    if (mr(d))
        push(d);
    else
        dfs(d);
    if (mr(d2))
        push(d2);
    else
        dfs(d2);
}

ll getfact(ll n)
{
    mxp = 0;
    if (mr(n))
        return n;
    else
        dfs(n);
    return mxp;
}
using std::cin;
using std::cout;
void solve()
{
    long long n;
    cin >> n;
    if (n == 1)
    {
        cout << 1 << ' ';
        return;
    }
    auto tp = getfact(n), tmp = n;
    while (n % tp == 0)
        n /= tp;
    if (n == 1)
        cout << tp % P << ' ';
    else
        cout << 1 << ' ';
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}