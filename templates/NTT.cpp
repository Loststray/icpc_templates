#include <bits/stdc++.h>
using namespace std;
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
mint ar[N], br[N];
int rev[N];
template<typename T>
void Butterfly_Transform(T f[], int len)
{
    for (int i = 0; i < len; i++)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++)
        if (i < rev[i])
            swap(f[i], f[rev[i]]);
}
void NTT(mint f[], int len, int op)
{
    Butterfly_Transform(f, len);
    for (int i = 2; i <= len; i <<= 1)
    {
        mint step = op == -1 ? 332748118 : 3;
        step = step.pow((P - 1) / i);
        for (int j = 0; j < len; j += i)
        {
            mint cur = 1;
            for (int k = j; k < j + i / 2; k++)
            {
                auto a = f[k], b = cur * f[k + i / 2];
                f[k] = a + b;
                f[k + i / 2] = a - b;
                cur *= step;
            }
        }
    }
    if (op == -1)
    {
        mint inv(len);
        inv = inv.inv();
        for (int i = 0; i < len; i++)
            f[i] *= inv;
    }
}
mint tmpa[N], tmpb[N];

void cdq_NTT(mint *f, mint *g, int l, int r)
{
    if (l == r)
    {
        if (!l)
            f[l] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    cdq_NTT(f, g, l, mid);
    memcpy(tmpa, f + l, sizeof(mint) * (mid - l + 1));
    memcpy(tmpb, g, sizeof(mint) * (r - l + 1));
    int len = 2;
    while (len <= r - l + 1)
        len <<= 1;
    fill(tmpa + mid - l + 1, tmpa + len + 1, 0);
    fill(tmpb + r - l + 1, tmpb + len + 1, 0);
    NTT(tmpa, len, 1);
    NTT(tmpb, len, 1);
    for (int i = 0; i < len; i++)
        tmpa[i] *= tmpb[i];
    NTT(tmpa, len, -1);
    for (int i = mid + 1; i <= r; i++)
        f[i] += tmpa[i - l];
    cdq_NTT(f, g, mid + 1, r);
}
void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
        cin >> br[i];
    cdq_NTT(ar, br, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << ar[i] << ' ';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}