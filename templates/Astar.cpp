#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 7;
const int M = 4e6 + 7;
map<long long, bool> vis;
const string tar = "123804765";
const int dir[4] = {-3, -1, 1, 3};
struct node
{
    string state;
    int dep;
};
bool heuristic(const string &x)
{
    int res = 0;
    for (int i = 0; i < 9; i++)
        res += x[i] != tar[i];
    return res;
};
bool operator<(const node &a, const node &b)
{
    return a.dep + heuristic(a.state) > b.dep + heuristic(b.state);
}

void solve()
{
    string curstate;
    cin >> curstate;
    priority_queue<node> q;
    q.push({curstate, 0});
    while (!q.empty())
    {
        auto [s, d] = q.top();
        q.pop();
        if (!heuristic(s))
        {
            cout << d << '\n';
            return;
        }
        if (vis[stoll(s)])
            continue;
        vis[stoll(s)] = 1;
        int pos = -1;
        for (int i = 0; i < 9; i++)
            if (s[i] == '0')
            {
                pos = i;
                break;
            }
        for (int i = 0; i < 4; i++)
        {
            if (pos % 3 == 0 && i == 1 || pos % 3 == 2 && i == 2)
                continue;
            int np = pos + dir[i];
            if (np >= 0 && np < 9)
            {
                swap(s[pos], s[np]);
                q.push({s, d + 1});
                swap(s[pos], s[np]);
            }
        }
    }
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