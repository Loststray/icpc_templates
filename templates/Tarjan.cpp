#include <bits/stdc++.h>
using namespace std;
const int N = 4e4 + 7;
namespace tarjan 
{
    int ar[N];
    int dfncnt, dfn[N], low[N];
    int s[N], top;
    int scc[N], siz[N], scccnt;
    bitset<N> vis;
    struct qxx
    {
        int to, nxt;
        // int val;
    } e[N << 1];
    int head[N], edge_cnt;
    void add_edge(int u, int v)
    {
        e[++edge_cnt] = {v, head[u]};
        head[u] = edge_cnt;
        top = 0;
    }
    void Tarjan(int u)
    {
        vis[u] = 1;
        low[u] = dfn[u] = ++dfncnt;
        s[++top] = u;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (!dfn[v])
            {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == dfn[u])
                {
                }
                /* 求割边/割点
                if (low[v] > dfn[u])
                {
                    isbridge[v] = 1;
                }*/
            }
            else if (vis[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u])
        {
            scccnt++;
            int k = s[top];
            do
            {
                k = s[top];
                vis[k] = 0;
                scc[k] = scccnt;
                siz[scccnt]++;
                top--;
            } while (k != u);
        }
    }
    void clear(int n)
    {
        fill(head, head + n + 1, 0);
        fill(dfn, dfn + n + 1, 0);
        top = dfncnt = scccnt = edge_cnt = 0;
    }
}

struct Two_SAT_BF
{
    vector<int> g[N];
    bitset<N> vis;
    int s[N], top, n;
    // 紧密储存 g[i] = true,g[i^1] = false, i = even;
    void clear(int n)
    {
        this->n = n;
        for (int i = 0; i < n * 2; i++)
            g[i].clear();
        vis.reset();
    }
    bool dfs(int x)
    {
        if (vis[x ^ 1])
            return 0;
        if (vis[x])
            return 1;
        vis[x] = 1;
        s[++top] = x;
        for (auto i : g[x])
            if (!dfs(i))
                return 0;
        return 1;
    }
    void add(int u, int v)
    {
        g[u].push_back(v);
    }
    bool solve()
    {
        for (int i = 0; i < n * 2; i++)
        {
            if (!vis[i] && !vis[i ^ 1])
            {
                top = 0;
                if (!dfs(i))
                {
                    while (top)
                        vis[s[top--]] = 0;
                    if (!dfs(i ^ 1))
                        return 0;
                }
            }
        }
        return 1;
    }
};
void solve()
{
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T;
    // cin >> T;
    // while(T--)
    solve();
    return 0;
}