#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 7;
struct Fenwich_Tree
{
    int n;
    long long c[N], ci[N];
    inline int lowbit(int x)
    {
        return x & -x;
    }
    void add(int x, int w)
    {
        for (int i = x; i <= n; i += lowbit(i))
            c[i] += w, ci[i] += x * w;
        return;
    }
    void range_add(int l, int r, int w) // 同时只可使用其一
    {
        add(l, w), add(r + 1, -w);
    }
    long long query(int x, long long *p)
    {
        long long ans = 0;
        for (int i = x; i; i -= lowbit(i))
            ans += p[i];
        return ans;
    }
    long long range_query(int l, int r) // [l,r]
    {
        return (r + 1ll) * query(r, c) - query(r, ci) - l * query(l - 1, c) + query(l - 1, ci);
    }
} fw;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    fw.n = n;
    for (int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        fw.range_add(i, i, t);
    }
    while (m--)
    {
        int op, x, y, k;
        cin >> op >> x;
        if (op == 1)
        {
            cin >> y >> k;
            fw.range_add(x, y, k);
        }
        else
            cout << fw.range_query(x, x) << '\n';
    }
}