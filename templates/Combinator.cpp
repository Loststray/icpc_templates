#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 3e5 + 7;
const int P = 998244353;
template <const int T>
struct ModInt
{
    const static int mod = T;
    int x;
    ModInt(int x = 0) : x(x % mod) {}
    ModInt(long long x) : x(int(x % mod)) {}
    int val() { return x; }
    ModInt operator+(const ModInt &a) const
    {
        int x0 = x + a.x;
        return ModInt(x0 < mod ? x0 : x0 - mod);
    }
    ModInt operator-(const ModInt &a) const
    {
        int x0 = x - a.x;
        return ModInt(x0 < 0 ? x0 + mod : x0);
    }
    ModInt operator*(const ModInt &a) const { return ModInt(1LL * x * a.x % mod); }
    ModInt operator/(const ModInt &a) const { return *this * a.inv(); }
    void operator+=(const ModInt &a)
    {
        x += a.x;
        if (x >= mod)
            x -= mod;
    }
    void operator-=(const ModInt &a)
    {
        x -= a.x;
        if (x < 0)
            x += mod;
    }
    void operator*=(const ModInt &a) { x = 1LL * x * a.x % mod; }
    void operator/=(const ModInt &a) { *this = *this / a; }
    friend ModInt operator+(int y, const ModInt &a)
    {
        int x0 = y + a.x;
        return ModInt(x0 < mod ? x0 : x0 - mod);
    }
    friend ModInt operator-(int y, const ModInt &a)
    {
        int x0 = y - a.x;
        return ModInt(x0 < 0 ? x0 + mod : x0);
    }
    friend ModInt operator*(int y, const ModInt &a) { return ModInt(1LL * y * a.x % mod); }
    friend ModInt operator/(int y, const ModInt &a) { return ModInt(y) / a; }
    friend ostream &operator<<(ostream &os, const ModInt &a) { return os << a.x; }
    friend istream &operator>>(istream &is, ModInt &t) { return is >> t.x; }

    ModInt pow(int64_t n) const
    {
        ModInt res(1), mul(x);
        while (n)
        {
            if (n & 1)
                res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }

    ModInt inv() const
    {
        int a = x, b = mod, u = 1, v = 0;
        while (b)
        {
            int t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        if (u < 0)
            u += mod;
        return u;
    }
};
typedef ModInt<P> mint;

mint fact[N], invfact[N];

void init()
{
    fact[0] = invfact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i;
    invfact[N - 1] = fact[N - 1].inv();
    for (int i = N - 2; i; i--)
        invfact[i] = invfact[i + 1] * (i + 1);
}

inline mint C(int a, int b)
{
    if (a < 0 || b < 0 || a < b)
        return 0;
    return fact[a] * invfact[b] * invfact[a - b];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    auto foo = [&](int n)
    {
        return n;
    };
    cout << foo(1) << '\n';
}