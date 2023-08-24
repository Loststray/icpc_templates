#include <bits/stdc++.h>
using namespace std;
const int N = 205;
const int M = 1e4 + 7;
const int GN = 1205;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
struct qxx
{
    int to, nxt;
    long long res;
};
struct Edmonds_Karp
{
    int tot = 1;
    qxx e[N * 1000];
    int head[N], pre[N];
    long long nodeflow[N];
    void clear()
    {
        memset(head, 0, sizeof(head));
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
    long long Maxflow(int s, int t)
    {
        long long ans = 0;
        while (1)
        {
            memset(nodeflow, 0, sizeof(nodeflow));
            queue<int> q;
            q.push(s);
            nodeflow[s] = LINF;
            while (!q.empty())
            {
                int x = q.front();
                q.pop();
                for (int i = head[x]; i; i = e[i].nxt)
                {
                    if (!nodeflow[e[i].to] && e[i].res > 0)
                    {
                        pre[e[i].to] = i;
                        nodeflow[e[i].to] = min(nodeflow[x], e[i].res);
                        q.push(e[i].to);
                    }
                }
                if (nodeflow[t])
                    break;
            }
            if (!nodeflow[t])
                break;
            for (int u = t; u != s; u = e[pre[u] ^ 1].to)
            {
                e[pre[u]].res -= nodeflow[t];
                e[pre[u] ^ 1].res += nodeflow[t];
            }
            ans += nodeflow[t];
        }
        return ans;
    }
} EK;

namespace Dinic
{
    int n, s, t;
    int tot = 1, head[N];
    struct qxx
    {
        int to, nxt;
        long long res;
    } e[M];
    int level[N], cur[N];
    void clear(int n)
    {
        Dinic::n = n;
        fill(head, head + n + 1, 0);
        tot = 1;
    }
    void addedge(int u, int v, long long cap)
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
        fill(level,level + n + 1,0);
        queue<int> q;
        q.push(s);
        level[s] = 1;
        cur[s] = head[s];
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = head[x]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (!level[v] && e[i].res > 0)
                {
                    cur[v] = head[v];
                    level[v] = level[x] + 1;
                    q.push(v);
                }
            }
        }
        return level[t];
    }
    long long dfs(int x, long long res)
    {
        if (x == t || !res)
            return res;
        long long flow = res;
        for (int &i = cur[x]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (!e[i].res || level[v] != level[x] + 1)
                continue;
            long long f = dfs(v, min(flow, e[i].res));
            if (f > 0)
            {
                e[i].res -= f;
                e[i ^ 1].res += f;
                flow -= f;
                if (!flow)
                    break;
            }
            else
                level[v] = 0;
        }
        return res - flow;
    }
    long long Maxflow(int s, int t)
    {
        Dinic::s = s;
        Dinic::t = t;
        long long ans = 0;
        while (bfs())
        {
            ans += dfs(s, INT32_MAX >> 1);
        }
        return ans;
    }
};

struct ISAP
{
    int n, m, s, t;
    int tot = 1, head[N];
    qxx e[M];
    int level[N], cur[N], pre[N], gap[N];
    void clear(int n)
    {
        this->n = n;
        memset(head, 0, sizeof(head));
        tot = 1;
    }
    void addedge(int u, int v, long long w)
    {
        e[++tot].to = v;
        e[tot].res = w;
        e[tot].nxt = head[u];
        head[u] = tot;
        e[++tot].to = u;
        e[tot].res = 0;
        e[tot].nxt = head[v];
        head[v] = tot;
    }
    bool bfs()
    {
        queue<int> q;
        q.push(t);
        level[t] = 0;
        gap[0] = 1;
        cur[t] = head[t];
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = head[x]; i; i = e[i].nxt)
            {
                int u = e[i].to;
                if (level[u] == -1)
                {
                    cur[u] = head[u];
                    level[u] = level[x] + 1;
                    gap[level[u]]++;
                    q.push(u);
                }
            }
        }
        return level[s] != -1;
    }
    long long Aug()
    {
        int x = t;
        long long res = LINF;
        while (x != s)
        {
            res = min(res, e[pre[x]].res);
            x = e[pre[x] ^ 1].to;
        }
        x = t;
        while (x != s)
        {
            e[pre[x]].res -= res;
            e[pre[x] ^ 1].res += res;
            x = e[pre[x] ^ 1].to;
        }
        return res;
    }
    long long Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        long long flow = 0;
        memset(level, -1, sizeof(level));
        memset(gap, 0, sizeof(gap));
        if (!bfs())
            return 0;
        int x = s;
        // memcpy(cur, head, sizeof(head));
        while (level[s] < n)
        {
            if (x == t)
            {
                flow += Aug();
                x = s;
            }
            bool flag = 0;
            for (int &i = cur[x]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (level[x] == level[v] + 1 && e[i].res > 0)
                {
                    flag = 1;
                    pre[v] = i;
                    x = v;
                    break;
                }
            }
            if (!flag)
            {
                int k = n;
                for (int i = head[x]; i; i = e[i].nxt)
                    if (e[i].res > 0)
                        k = min(k, level[e[i].to]);
                if (--gap[level[x]] == 0)
                    return flow;
                gap[level[x] = k + 1]++;
                cur[x] = head[x];
                if (x != s)
                    x = e[pre[x] ^ 1].to;
            }
        }
        return flow;
    }
} IMSP;

struct HLPP
{
    int n, m, s, t;
    long long level = 0;
    int head[N], tot = 1;
    qxx e[N * 200];
    long long ht[N], exc[N], gap[N];
    stack<int> buk[N];
    void clear(int n)
    {
        this->n = n;
        memset(head, 0, sizeof(head));
        memset(exc, 0, sizeof(exc));
        level = 0;
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
    bool push(int u)
    {
        bool flag = u == s;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            const int &v = e[i].to;
            if (!e[i].res || !flag && ht[u] != ht[v] + 1)
                continue;
            long long k = flag ? e[i].res : min(e[i].res, exc[u]);
            if (v != s && v != t && !exc[v] && ht[v] != LINF)
            {
                buk[ht[v]].push(v);
                level = max(level, ht[v]);
            }
            exc[u] -= k;
            exc[v] += k;
            e[i].res -= k;
            e[i ^ 1].res += k;
            if (!exc[u])
                return 0;
        }
        return 1;
    }
    void relabel(int u)
    {
        ht[u] = LINF;
        for (int i = head[u]; i; i = e[i].nxt)
            if (e[i].res)
                ht[u] = min(ht[u], ht[e[i].to]);
        if (++ht[u] < n)
        {
            buk[ht[u]].push(u);
            level = max(level, ht[u]);
            ++gap[ht[u]];
        }
    }
    bool bfs()
    {
        memset(ht, 0x3f, sizeof(ht));
        queue<int> q;
        q.push(t);
        ht[t] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i; i = e[i].nxt)
                if (e[i ^ 1].res && ht[e[i].to] > ht[u] + 1)
                    ht[e[i].to] = ht[u] + 1, q.push(e[i].to);
        }
        return ht[s] != LINF;
    }
    int top()
    {
        while (!buk[level].size() && level >= 0)
            level--;
        return level == -1 ? 0 : buk[level].top();
    }
    long long Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        if (!bfs())
            return 0;
        memset(gap, 0, sizeof(gap));
        for (int i = 1; i <= n; i++)
            if (ht[i] != LINF)
                gap[ht[i]]++;
        ht[s] = n;
        push(s);
        int u;
        while ((u = top()))
        {
            buk[level].pop();
            if (push(u))
            {
                if (!--gap[ht[u]])
                    for (int i = 1; i <= n; i++)
                        if (i != s && i != t && ht[i] > ht[u] && ht[i] < n + 1)
                            ht[i] = n + 1;
                relabel(u);
            }
        }
        return exc[t];
    }
} hlppz;
void solve()
{
    // int n, m, s, t;
    // scanf("%d %d %d %d", &n, &m, &s, &t);
    // Dick.clear(n);
    // for (int i = 0; i < m; i++)
    // {
    //     int u, v;
    //     long long cap;
    //     scanf("%d %d %lld", &u, &v, &cap);
    //     Dick.addedge(u, v, cap);
    // }
    // printf("%lld\n", Dick.Maxflow(s, t));
}
int main()
{
    // int T;
    // cin >> T;
    // while(T--)
    solve();
}