#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 7;

void solve()
{
    int n, q;
    cin >> n >> q;
    const int sz = sqrt(n);
    vector<int> ar(n + 1), id(n + 1), block(sz + 2), cnt(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> ar[i];
        id[i] = (i + sz - 1) / sz;
    }
    vector<array<int, 3>> queries(q + 1);
    for (int i = 1; i <= q; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
    }
    sort(++queries.begin(), queries.end(), [&id](const array<int, 3> &a, const array<int, 3> &b)
         { if (id[a[0]] == id[b[0]]) return a[1] < b[1]; return id[a[0]] < id[b[0]]; });
    int sum = 0;
    auto update = [&](int x, int op) -> void
    {
        if (op == 1)
            sum += cnt[x]++;
        else
            sum -= --cnt[x];
    };
    vector<array<int, 2>> ans(q + 1);
    for (int i = 1, l = 1, r = 0; i <= q; i++)
    {
        auto &[L, R, id] = queries[i];
        while (l > L)
            update(ar[--l], 1);
        while (r < R)
            update(ar[++r], 1);
        while (l < L)
            update(ar[l++], -1);
        while (r > R)
            update(ar[r--], -1);
        ans[id][0] = sum;
        ans[id][1] = 1ll * (r - l + 1) * (r - l) / 2;
    }
    for (int i = 1; i <= q; i++)
    {
        auto &[a, b] = ans[i];
        if (a)
        {
            int gcd = __gcd(a, b);
            a /= gcd;
            b /= gcd;
        }
        else
            b = 1;
        cout << a << '/' << b << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}