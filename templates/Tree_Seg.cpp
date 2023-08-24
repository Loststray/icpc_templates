#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
const int M = 2e5 + 7;
const double eps = 1e-5;
int P;
struct qxx
{
    int to, nxt;
} e[M];
int head[N], edge_cnt;
int par[N], dep[N], sz[N], Hson[N], top[N], id[N], rk[N], node_tot;
long long ar[N];
void add_edge(int u, int v)
{
    e[++edge_cnt].to = v;
    e[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}
void dfs_Init(int u, int Par)
{
    par[u] = Par;
    dep[u] = dep[Par] + 1;
    sz[u] = 1;
    Hson[u] = -1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == Par)
            continue;
        dfs_Init(v, u);
        sz[u] += sz[v];
        if (Hson[u] == -1 || sz[v] > sz[Hson[u]])
            Hson[u] = v;
    }
}
void dfs_work(int u, int t)
{
    top[u] = t;
    id[u] = ++node_tot;
    rk[node_tot] = u;
    if (Hson[u] == -1)
        return;
    dfs_work(Hson[u], t);
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v != Hson[u] && v != par[u])
            dfs_work(v, v);
    }
}
int LCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = par[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u,v);
    return u;
}
struct Seg_Tree
{
    long long val[N << 2], ls[N << 2], rs[N << 2], lazy[N << 2];
    // sum Tree
    void build(int l, int r, int p)
    {
        ls[p] = l;
        rs[p] = r;
        if (l == r)
        {
            val[p] = ar[rk[l]] % P;
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        (val[p] = val[p << 1] + val[p << 1 | 1]) %= P;
    }
    void pushdown(int p)
    {
        int mid = ls[p] + rs[p] >> 1;
        (val[p << 1] += lazy[p] * (mid - ls[p] + 1)) %= P;
        (val[p << 1 | 1] += lazy[p] * (rs[p] - mid)) %= P;
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
    }
    void update(int l, int r, int x, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
        {
            (val[p] += (rs[p] - ls[p] + 1) * x) %= P;
            lazy[p] += x;
            return;
        }
        if (lazy[p])
            pushdown(p);
        int mid = ls[p] + rs[p] >> 1;
        if (l <= mid)
            update(l, r, x, p << 1);
        if (r > mid)
            update(l, r, x, p << 1 | 1);
        (val[p] = val[p << 1] + val[p << 1 | 1]) %= P;
    }
    long long query(int l, int r, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
        {
            return val[p];
        }
        if (lazy[p])
            pushdown(p);
        long long mid = ls[p] + rs[p] >> 1, res = 0;
        if (l <= mid)
            res += query(l, r, p << 1);
        if (r > mid)
            res += query(l, r, p << 1 | 1);
        return res % P;
    }
} ST;
long long query_sum(int u, int v)
{
    long long res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        (res += ST.query(id[top[u]], id[u], 1)) %= P;
        u = par[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    (res += ST.query(id[u], id[v], 1)) %= P;
    return res;
}
void update_wow(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] > dep[top[v]])
        {
            ST.update(id[top[u]], id[u], w, 1);
            u = par[top[u]];
        }
        else
        {
            ST.update(id[top[v]], id[v], w, 1);
            v = par[top[v]];
        }
    }
    if (dep[u] > dep[v])
        ST.update(id[v], id[u], w, 1);
    else
        ST.update(id[u], id[v], w, 1);
}
long long queryson(int u)
{
    return ST.query(id[u], id[u] + sz[u] - 1, 1);
}
void updateson(int u, int w)
{
    ST.update(id[u], id[u] + sz[u] - 1, w, 1);
}
void solve()
{
    int n, m, root;
    cin >> n >> m >> root >> P;
    for (int i = 1; i <= n; i++)
        cin >> ar[i];
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs_Init(root, 0);
    dfs_work(root, root);
    ST.build(1, node_tot, 1);
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int u, v, w;
            cin >> u >> v >> w;
            update_wow(u, v, w);
        }
        else if (op == 2)
        {
            int u, v;
            cin >> u >> v;
            cout << query_sum(u, v) << '\n';
        }
        else if (op == 3)
        {
            int u, w;
            cin >> u >> w;
            updateson(u, w);
        }
        else
        {
            int u;
            cin >> u;
            cout << queryson(u) << '\n';
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}