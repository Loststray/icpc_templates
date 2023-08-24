#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
struct qxx
{
    int to, nxt;
    // int val;
}e[N << 1];
int head[N],edge_cnt;
void add_edge(int u,int v)
{
    e[++edge_cnt] = {v,head[u]};
    head[u] = edge_cnt;
}
void clear(int n)
{
    fill(head,head + n + 1,0);
    edge_cnt = 0;
}
void solve()
{
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}