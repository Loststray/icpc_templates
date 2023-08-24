#include <bits/stdc++.h>
using namespace std;
// ax + by = gcd(a,b)
// ax ≡ c mod b
long long exgcd(long long a, long long b, long long &x, long long &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}
// CRT
void solve()
{
    int n;
    long long prodn = 1;
    cin >> n;
    vector<long long> mod(n + 1), remain(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> mod[i] >> remain[i];
        prodn *= mod[i];
    }
    long long res = 0;
    for (int i = 1; i <= n; i++)
    {
        long long m = prodn / mod[i], b, y;
        exgcd(m, mod[i], b, y);
        (res += b * m * remain[i] % prodn + prodn) %= prodn;
    }
    cout << res << '\n';
}
void out(__int128_t x)
{
    if (x >= 10)
        out(x / 10);
    cout << (int)(x % 10);
}
void exCRT()
{
    int n;
    cin >> n;
    vector<long long> modulus(n + 1), remain(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> modulus[i] >> remain[i];
    __int128_t prodn = modulus[1], res = remain[1];
    for (int i = 2; i <= n; i++)
    {
        long long x, y;
        long long d = exgcd(prodn, modulus[i], x, y);
        if ((remain[i] - res) % d)
        {
            // NULL
            return;
        }
        __int128_t lcm = prodn / d * modulus[i],
        tmp = ((remain[i] - res) / d) % (modulus[i] / d);
        (res += prodn * x * tmp % lcm + lcm) %= lcm;
        prodn = lcm;
    }
    // cout << res << '\n';
    if (!res)
        res = prodn;
    out(res);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    exCRT();
    return 0;
}