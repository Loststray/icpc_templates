#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 7;
typedef std::complex<double> comp;
const double PI = acos(-1);
const comp I(0, 1);
comp *ar, *br;
int *rev;
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
template <typename T>
void Butterfly_Transform(T f[], int len)
{
    for (int i = 0; i < len; i++)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++)
        if (i < rev[i])
            swap(f[i], f[rev[i]]);
}
void FFT(comp *f, int len, int op)
{
    Butterfly_Transform(f, len);
    for (int i = 2; i <= len; i <<= 1)
    {
        comp step = exp(2 * op * PI / i * I);
        for (int j = 0; j < len; j += i)
        {
            comp cur(1, 0);
            for (int k = j; k < j + i / 2; k++)
            {
                comp a = f[k];
                comp b = cur * f[k + i / 2];
                f[k] = a + b;
                f[k + i / 2] = a - b;
                cur = cur * step;
            }
        }
    }
    if (op == -1)
    {
        for (int i = 0; i < len; i++)
        {
            f[i].real(f[i].real() / len);
        }
    }
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
namespace poly
{
    using comp = complex<double>;
    const double PI = acos(-1);
    const comp I(0, 1);
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
    int rev[N];
    bool flag = 0;
    mint wow[N], res[N], C[N];
    template <typename T>
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
    mint *qpower(mint *a, int b, int len, int n)
    {
        auto res = new mint[len];
        while (b)
        {
            NTT(a, len, 1);
            if (b & 1)
            {
                NTT(res, len, 1);
                for (int i = 0; i < len; i++)
                    res[i] *= a[i];
                NTT(res, len, -1);
                for (int i = n + 1; i < len; i++)
                    res[i] = 0;
            }
            for (int i = 0; i < len; i++)
                a[i] *= a[i];
            NTT(a, len, -1);
            for (int i = n + 1; i < len; i++)
                a[i] = 0;
            b /= 2;
        }
        return res;
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    int len = 1;
    while (len <= n + m)
        len <<= 1;
    ar = new comp[len];
    br = new comp[len];
    rev = new int[len];
    fill(ar, ar + len, 0);
    fill(br, br + len, 0);
    fill(rev, rev + len, 0);
    /*
     */
    for (int i = 0; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        ar[i].real(tmp);
    }
    for (int i = 0; i <= m; i++)
    {
        int tmp;
        cin >> tmp;
        br[i].real(tmp);
    }
    FFT(ar, len, 1);
    FFT(br, len, 1);
    for (int i = 0; i <= len; i++)
        ar[i] *= ar[i];
    FFT(ar, len, -1);
    for (int i = 0; i <= m + n; i++)
        cout << (int)round(ar[i].real()) << ' ';
    delete[] ar;
    delete[] br;
    delete[] rev;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    solve();
    return 0;
}