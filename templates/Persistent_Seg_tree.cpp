// 这回只花了114514min就打完了。
// 真好。记得多手造几组。最好有暴力对拍。
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
const int M = 2e3 + 7;
const int P = 998244353;
struct info
{
    int val, Lson, Rson;
    info() : val(0), Lson(0), Rson(0) {}
    info(int x) : val(x), Lson(0), Rson(0) {}
};
struct Seg_Tree_Sus
{
    vector<info> val;
    int nodecnt{-1};
    int build(int l, int r)
    {
        int p = val.size();
        val.push_back(info());
        if (l == r)
            return p;
        int mid = l + r >> 1;
        val[p].Lson = build(l, mid);
        val[p].Rson = build(mid + 1, r);
        return p;
    }
    int newnode(int p)
    {
        val.push_back(val[p]);
        val.back().val++;
        return val.size() - 1;
    }
    int update(int x, int L, int R, int p)
    {
        p = newnode(p);
        if (L == R)
            return p;
        int mid = L + R >> 1;
        if (x <= mid)
            val[p].Lson = update(x, L, mid, val[p].Lson);
        else
            val[p].Rson = update(x, mid + 1, R, val[p].Rson);
        return p;
    }
    int query(int u, int v, int L, int R, int k)
    {
        if (L == R)
        {
            return L;
        }
        int x = val[val[v].Lson].val - val[val[u].Lson].val;
        int mid = L + R >> 1;
        if (x >= k)
            return query(val[u].Lson, val[v].Lson, L, mid, k);
        else
            return query(val[u].Rson, val[v].Rson, mid + 1, R, k - x);
    }
} ST;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> ar(n + 1);
    for (int i=1;i<=n;i++)
        cin >> ar[i];
    vector<int> ori(ar);
    sort(++ar.begin(), ar.end());
    auto ed = unique(++ar.begin(), ar.end());
    for (auto &it : ori)
        it = lower_bound(++ar.begin(), ed, it) - ar.begin();
    const int len = ed - ar.begin() - 1;
    vector<int> roots(n + 1);
    roots[0] = ST.build(1, len);
    for (int i = 1; i <= n; i++)
        roots[i] = ST.update(ori[i], 1, len, roots[i - 1]);
    for (int i = 1; i <= m; i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        cout << ar[ST.query(roots[l - 1], roots[r], 1, len, k)] << '\n';
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}