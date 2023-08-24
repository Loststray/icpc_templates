// 这回只花了114514min就打完了。
// 真好。记得多手造几组。最好有暴力对拍。
#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 7;
const int M = 2e3 + 7;
const int P = 998244353;
struct info
{
    int cursegs, cnt, len;
    bool lflag, rflag;
    info() : cursegs(0), cnt(0), len(0), lflag(0), rflag(0) {}
};
info operator+(const info &a, const info &b)
{
    info res;
    res.len = a.len + b.len;
    res.cnt = a.cnt + b.cnt - (a.rflag && b.lflag);
    res.lflag = a.lflag;
    res.rflag = b.rflag;
    return res;
}
struct seg_tree
{
    info val[N << 2];
    int L[N << 2], R[N << 2];
    void operate(int l, int r, int w, int p)
    {
        if (val[p].cursegs)
        {
            val[p].len = r - l + 1;
            val[p].cnt = 1;
            val[p].lflag = 1;
            val[p].rflag = 1;
        }
        else if (l == r)
            val[p] = info();
        else
            val[p] = val[p << 1] + val[p << 1 | 1];
    }
    void build(int l, int r, int p = 1)
    {
        L[p] = l;
        R[p] = r;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
    }
    void update(int l, int r, int w, int p = 1)
    {
        if (l <= L[p] && R[p] <= r)
        {
            val[p].cursegs += w;
            operate(L[p], R[p], w, p);
            return;
        }
        int mid = (L[p] + R[p]) >> 1;
        if (l <= mid)
            update(l, r, w, p << 1);
        if (r > mid)
            update(l, r, w, p << 1 | 1);
        operate(L[p], R[p], w, p);
    }
} ST;

void solve()
{

    int n;
    cin >> n;
    vector<array<int, 4>> opts;
    int Lbound = INT32_MAX, Rbound = INT32_MIN;
    for (int i = 1; i <= n; i++)
    {
        int sx, sy, tx, ty;
        cin >> sx >> sy >> tx >> ty;
        opts.push_back({sy, sx, tx, 1});
        opts.push_back({ty, sx, tx, -1});
        Lbound = min(Lbound, sx);
        Rbound = max(Rbound, tx);
    }
    ST.build(Lbound, Rbound);
    sort(opts.begin(), opts.end(), [&](const array<int, 4> &a, const array<int, 4> &b)
         { return a[0] < b[0] || a[0] == b[0] && a[3] > b[3]; });
    auto pre = 0;
    long long res = 0;
    const int len = opts.size() - 1;
    for (int i = 0; i <= len; i++)
    {
        auto [cur, l, r, f] = opts[i];
        ST.update(l, r - 1, f);
        res += abs(ST.val[1].len - pre);
        pre = ST.val[1].len;
        if (i != len)
            res += ST.val[1].cnt * 2 * (opts[i + 1][0] - cur);
    }
    cout << res << '\n';
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