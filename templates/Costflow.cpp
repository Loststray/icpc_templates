#include <bits/stdc++.h>
using namespace std;
const int N = 5000;
const int INF = 0x3f3f3f3f;
struct point
{
    int x, y;
};
struct qxx
{
    int to, nxt;
    long long res, cost;
};
struct C_Dinic
{
    int n, m, s, t;
    long long ans;
    int head[N], tot = 1;
    qxx e[N * 100];
    int dis[N], cur[N];
    bitset<N> vis;
    void clear()
    {
        memset(head, 0, sizeof(head));
        tot = 1;
    }
    void addedge(int u, int v, int cap, int cost)
    {
        e[++tot].to = v;
        e[tot].res = cap;
        e[tot].cost = cost;
        e[tot].nxt = head[u];
        head[u] = tot;
        e[++tot].to = u;
        e[tot].res = 0;
        e[tot].cost = -cost;
        e[tot].nxt = head[v];
        head[v] = tot;
    }
    bool spfa()
    {
        memset(dis, 0x3f, sizeof(dis));
        memcpy(cur, head, sizeof(head));
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        dis[s] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; i; i = e[i].nxt)
            {
                if (e[i].res > 0 && dis[e[i].to] > dis[e[i ^ 1].to] + e[i].cost)
                {
                    dis[e[i].to] = dis[e[i ^ 1].to] + e[i].cost;
                    if (!vis[e[i].to])
                    {
                        vis[e[i].to] = 1;
                        q.push(e[i].to);
                    }
                }
            }
        }
        return dis[t] != INF;
    }
    long long Cdfs(int x, long long res)
    {
        if (x == t || !res)
            return res;
        long long flow = res, f;
        vis[x] = 1;
        for (int &i = cur[x]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (!e[i].res || vis[v] || dis[v] != dis[x] + e[i].cost)
                continue;
            f = Cdfs(v, min(flow, e[i].res));
            if (f > 0)
            {
                ans += f * e[i].cost;
                e[i].res -= f;
                e[i ^ 1].res += f;
                flow -= f;
                if (!flow)
                    break;
            }
            else
                dis[v] = 0;
        }
        vis[x] = 0;
        return res - flow;
    }
    long long Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        long long flow = 0;
        ans = 0;
        while (spfa())
        {
            vis.reset();
            flow += Cdfs(s, INF);
        }
        return ans;
    }
} CDick;
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1, vector<int>(n + 1));
    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j], pre[j] += g[i][j];
    int s = 0, t = n << 1 | 1;
    for (int i = 1; i <= n; i++)
        CDick.addedge(s, i, 1, 0);
    for (int i = n + 1; i <= n << 1; i++)
        CDick.addedge(i, t, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            CDick.addedge(i, j + n, 1, pre[j] - g[i][j]);
    cout << CDick.Maxflow(s, t);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    solve();
    return 0;
}