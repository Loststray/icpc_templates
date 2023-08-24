#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
const int GN = 1205;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
struct qxx
{
    int to, nxt;
    long long res;
};
struct Hungary
{
    int tot = 1, head[N];
    qxx e[N * 10];
    bitset<N> vis;
    int xx[N], yy[N], n;
    void addedge(int u, int v)
    {
        e[++tot].to = v;
        e[tot].res = 1;
        e[tot].nxt = head[u];
        head[u] = tot;
    }
    bool dfs(int x)
    {
        for (int i = head[x]; i; i = e[i].nxt)
        {
            int y = e[i].to;
            if (!vis[y])
            {
                vis[y] = 1;
                if (yy[y] == -1 || dfs(yy[y]))
                {
                    xx[x] = y;
                    yy[y] = x;
                    return 1;
                }
            }
        }
        return 0;
    }
    int Maximum_Matching(int n)
    {
        int ans = 0;
        memset(xx, -1, sizeof(xx));
        memset(yy, -1, sizeof(yy));
        for (int i = 1; i <= n; i++)
        {
            if (xx[i] == -1)
            {
                vis.reset();
                if (dfs(i))
                    ans++;
            }
        }
        return ans;
    }
} Hun;

struct Dinic
{
    int n, m, s, t;
    int tot = 1, head[N];
    qxx e[N * 10];
    int level[N], cur[N];
    bitset<N> vis;
    void clear()
    {
        memset(head, 0, sizeof(head));
        memset(level, 0, sizeof(cur));
        tot = 1;
    }
    void addedge(int u, int v, int cap)
    {
        e[++tot].to = v;
        e[tot].res = cap;
        e[tot].nxt = head[u];
        head[u] = tot;
        e[++tot].to = u;
        e[tot].res = 0;
        e[tot].nxt = head[v];
        head[v] = tot;
    }
    bool bfs()
    {
        vis.reset();
        queue<int> q;
        q.push(s);
        level[s] = 0;
        vis[s] = 1;
        cur[s] = head[s];
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = head[x]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (!vis[v] && e[i].res > 0)
                {
                    vis[v] = 1;
                    cur[v] = head[v];
                    level[v] = level[x] + 1;
                    q.push(v);
                }
            }
        }
        return vis[t];
    }
    long long dfs(int x, long long res)
    {
        if (x == t || !res)
            return res;
        long long flow = 0, f;
        for (int i = cur[x]; i; i = e[i].nxt)
        {
            cur[x] = i;
            int v = e[i].to;
            if (level[x] + 1 == level[v] && (f = dfs(v, min(res - flow, e[i].res))) > 0)
            {
                e[i].res -= f;
                e[i ^ 1].res += f;
                flow += f;
                res -= f;
                if (!res)
                    break;
            }
        }
        return flow;
    }
    long long Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        long long ans = 0;
        while (bfs())
        {
            ans += dfs(s, INF);
        }
        return ans;
    }
} Dick;

int main()
{
    ios::sync_with_stdio(0);
    // cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int l1, l2;
        cin >> l1 >> l2;
        Hun.addedge(l1, i);
        Hun.addedge(l2, i);
    }
    cout << Hun.Maximum_Matching(n) << endl;
}
