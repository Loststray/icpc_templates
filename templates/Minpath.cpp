#include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 7;
const int M = 1e5 + 7;
const int INF = 0x3f3f3f3f;
struct node
{
    int v, to;
    bool operator>(const node &a) const { return to > a.to; }
};
struct qxx
{
    int to, nxt;
    long long val;
};

struct Dijk // O(mlogm)
{
    struct node
    {
        long long v, to;
        bool operator>(const node &a) const { return to > a.to; }
    };
    struct qxx
    {
        int to, nxt;
        long long val;
    };
    long long dis[N], head[N], tot;
    qxx e[M];
    bitset<N> vis;
    void clear(int n)
    {
        fill(head,head + n + 1,0);
        tot = 0;
    }
    inline void addedge(int u, int v, int val)
    {
        e[++tot].to = v;
        e[tot].val = val;
        e[tot].nxt = head[u];
        head[u] = tot;
    }
    const long long &operator[](int x) const { return dis[x]; }
    long long &operator[](int x) { return dis[x]; }
    void Minpath(int s)
    {
        memset(dis, 0x3f, sizeof(dis));
        vis.reset();
        dis[s] = 0;
        priority_queue<node, vector<node>, greater<node>> q;
        q.push({s, 0});
        while (!q.empty())
        {
            int u = q.top().v;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = 1;
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (dis[v] > dis[u] + e[i].val)
                {
                    dis[v] = dis[u] + e[i].val;
                    q.push({v, dis[v]});
                }
            }
        }
    }
} dj;
struct Bellman_Ford // 负边权 O(nm)
{
    int dis[N], head[N], cnt[N], tot;
    qxx e[M];
    bitset<N> vis;
    void clear()
    {
        memset(head, 0, sizeof(head));
        tot = 0;
    }
    inline void addedge(int u, int v, int val)
    {
        e[++tot].to = v;
        e[tot].val = val;
        e[tot].nxt = head[u];
        head[u] = tot;
    }
    bool Minpath(int s, int n) // SPFA
    {
        for (int i = 1; i <= n; i++)
        {
            dis[i] = INF;
            cnt[i] = 0;
        }
        vis.reset();
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        vis[s] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to, w = e[i].val;
                if (dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= n)
                        return false;
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return true;
    }
    bool Maxpath(int s, int n) // SPFA
    {
        for (int i = 1; i <= n; i++)
        {
            dis[i] = -INF;
            cnt[i] = 0;
        }
        vis.reset();
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        vis[s] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to, w = e[i].val;
                if (dis[v] < dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= n)
                        return false;
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return true;
    }
} bf;
struct Johnson // O(nmlogm) B_F + DJ
{
    int dis[N], head[N], tot;
    qxx e[M];
    bitset<N> vis;
    long long ans[N][N];
    void clear(int n)
    {
        memset(head, 0, sizeof(head));
        tot = 0;
    }
    inline void addedge(int u, int v, int val)
    {
        e[++tot].to = v;
        e[tot].val = val;
        e[tot].nxt = head[u];
        head[u] = tot;
    }
    bool B_F(int n)
    {
        for (int i = 1; i <= n; i++)
            addedge(0, i, 0);
        bool f = 0;
        memset(dis, 0x3f, sizeof(dis));
        vis.reset();
        dis[0] = 0;
        vis[0] = 1;
        for (int i = 0; i <= n; i++)
        {
            f = 0;
            for (int u = 0; u <= n; u++)
            {
                if (dis[u] == INF)
                    continue;
                for (int k = head[u]; k; k = e[k].nxt)
                {
                    int v = e[k].to;
                    if (dis[v] > dis[u] + e[k].val)
                    {
                        dis[v] = dis[u] + e[k].val;
                        f = 1;
                    }
                }
            }
            if (!f)
                break;
        }
        return f;
    }
    bool Minpath(int n)
    {
        if (B_F(n))
            return 1;
        for (int u = 1; u <= n; u++)
        {
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                dj.addedge(u, v, e[i].val + dis[u] - dis[v]);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            dj.Minpath(i);
            for (int j = 1; j <= n; j++)
                ans[i][j] = dj.dis[j];
        }
        return 0;
    }

} js;

int main()
{
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v, val;
        cin >> u >> v >> val;
        js.addedge(u, v, val);
    }
    if (js.Minpath(n))
    {
        cout << -1;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            long long ans = 0;
            for (int j = 1; j <= n; j++)
            {
                if (js.ans[i][j] == INF)
                    ans += 1ll * j * 1e9;
                else
                    ans += 1ll * j * (js.ans[i][j] - js.dis[i] + js.dis[j]);
            }
            cout << ans << '\n';
        }
    }
}
