#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 7;
const int M = 1e4 + 7;
const double eps = 1e-5;
struct qxx
{
    int to, nxt;
} e[N << 1];
int head[N], edge_cnt, par[30][N], dep[N], lg[N];
long long dis[N];
void add_edge(int u, int v)
{
    e[++edge_cnt].to = v;
    e[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}
void dfs_Init(int u, int Par)
{
    par[0][u] = Par;
    dep[u] = dep[Par] + 1;
    for (int i = 1; i <= lg[dep[u]]; i++)
        par[i][u] = par[i - 1][par[i - 1][u]];
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == Par)
            continue;
        dfs_Init(v, u);
    }
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    while (dep[u] > dep[v])
        u = par[lg[dep[u] - dep[v]]][u];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; ~i; i--)
        if (par[i][u] != par[i][v])
            u = par[i][u], v = par[i][v];
    return par[0][u];
}
void solve(int n, int m, int c)
{
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs_Init(c, 0);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 2; i < N; i++)
        lg[i] = lg[i >> 1] + 1;
    int n, m, c;
    while (cin >> n >> m >> c)
        solve(n, m, c);
    return 0;
}