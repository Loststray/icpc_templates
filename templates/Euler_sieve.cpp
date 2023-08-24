#include <bits/stdc++.h>
using namespace std;
const int N = 1e8 + 7;
vector<int> prime, phi;
bitset<N> vis;
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
int main()
{
    int n, q;
    cin >> n >> q;
    euler(n);
    while (q--)
    {
        int tmp;
        cin >> tmp;
        cout << phi[tmp] << '\n';
    }
    return 0;
}