#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
const int P = 1e9 + 7;
vector<int> prime, phi;
bitset<N> vis, has_root;
void euler(int n)
{
    phi.resize(n + 1);
    vis.set();
    vis[1] = 0;
    phi[1] = 1;
    for (int i = 2; i < n; i++)
    {
        if (vis[i])
        {
            prime.emplace_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++)
        {
            vis[i * prime[j]] = 0;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
            {
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            }
        }
    }
    has_root[2] = has_root[4] = 1;
    for (auto p : prime)
    {
        if (p == 2)
            continue;
        for (int j = 1; 1ll * j * p < n; j *= p)
        {
            if (2ll * j * p < n)
                has_root[2 * j * p] = 1;
            has_root[j * p] = 1;
        }
    }
}
int getphi(int n)
{
    int ans = n;
    for (int i = 2, len = sqrt(n); i <= len; i++)
    {
        if (n % i == 0)
        {
            ans -= ans / i;
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        ans -= ans / n;
    return ans;
}
long long qpower(long long a, int b, int p)
{
    a %= p;
    long long res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b /= 2;
    }
    return res;
}
void solve()
{
    int n, d;
    cin >> n >> d;
    auto fac = [](int x)
    {
        vector<int> res;
        for (int i = 2; i <= x / i; i++)
        {
            if (x % i == 0)
            {
                while (x % i == 0)
                    x /= i;
                res.push_back(i);
            }
        }
        if (x != 1)
            res.push_back(x);
        return res;
    };
    if (has_root[n])
    {
        auto facs = fac(phi[n]);
        auto check = [&](int x, int p)
        {
            if (qpower(x, phi[p], p) != 1)
                return false;
            for (auto it : facs)
                if (qpower(x, phi[p] / it, p) == 1)
                    return false;
            return true;
        };
        auto find_min_root = [&](int p)
        {
            for (int i = 1; i < p; i++)
                if (check(i, p))
                    return i;
            return 0;
        };
        auto minroot = find_min_root(n);
        auto get_roots = [&](int p,int root)
        {
            long long pd = 1;
            vector<int> res;
            for(int i = 1;i <= phi[p];i++)
            {
                (pd *= root) %= p;
                if (gcd(i,phi[p]) == 1)
                    res.push_back(pd);
            }
            sort(res.begin(),res.end());
            return res;
        };
        auto ans = get_roots(n,minroot);
        cout << ans.size() << '\n';
        for(int i = d - 1,len = ans.size();i < len;i += d)
            cout << ans[i] << ' ';
        cout << '\n';
    }
    else
        cout << 0 << '\n' << '\n';
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    euler(N);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}