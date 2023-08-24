#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
const int M = 2e5 + 7;
const double eps = 1e-5;
struct qxx
{
    int to, nxt;
} e[M];
int head[N], edge_cnt;
void add_edge(int u, int v)
{
    e[++edge_cnt].to = v;
    e[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}
int Hson[N], sz[N], color[N], id[N], ls[N], rs[N], cnt[N], colorcnt, maxcolorsz[N], dfncnt;
void dfs_init(int u, int p)
{
    sz[u] = 1;
    ls[u] = ++dfncnt;
    id[dfncnt] = u;
    Hson[u] = -1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == p)
            continue;
        dfs_init(v, u);
        sz[u] += sz[v];
        if (Hson[u] == -1 || sz[Hson[u]] < sz[v])
            Hson[u] = v;
    }
    rs[u] = dfncnt;
}
void add(int u)
{
    if (!cnt[color[u]]++)
        colorcnt++;
    maxcolorsz[u] = max(maxcolorsz[u], cnt[color[u]]);
}
void del(int u)
{
    if (!--cnt[color[u]])
        colorcnt--;
}
int ans;
void dfs_Work(int u, int p, bool f)
{
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == p || v == Hson[u])
            continue;
        dfs_Work(v, u, false);
    }
    if (Hson[u] != -1)
        dfs_Work(Hson[u], u, true);
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == p || v == Hson[u])
            continue;
        for (int j = ls[v]; j <= rs[v]; j++)
            add(id[j]);
    }
    add(u);
    ans += (sz[u] % colorcnt == 0) && (sz[u] / colorcnt == maxcolorsz[u]);
    if (f == false)
        for (int i = ls[u]; i <= rs[u]; i++)
            if (!--cnt[color[id[i]]])
                colorcnt--;
}
void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int v;
        cin >> color[i] >> v;
        add_edge(v, i);
    }
    dfs_init(1, 0);
    dfs_Work(1, 0, 0);
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}