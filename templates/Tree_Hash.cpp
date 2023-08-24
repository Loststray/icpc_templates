#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 64;
const int P = 1e9 + 7;
const int Palt = 998244353;
map<vector<int>, int> Hash_Tree;
map<int, bool> sym;
int edge_cnt = 0;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<uint64_t> dist(0, ULLONG_MAX);
const uint64_t seed = dist(rnd);
size_t xorshift(size_t x)
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
int dfs(int u, int par, vector<vector<int>> &g)
{
    vector<int> child;
    for (auto v : g[u])
    {
        if (v == par)
            continue;
        child.emplace_back(dfs(v, u, g));
    }
    sort(child.begin(), child.end());
    if (!Hash_Tree.count(child))
    {
        map<int, int> cnt;
        for (auto v : child)
            cnt[v]++;
        int odd = 0;
        bool fuck = 0;
        for (auto &[x, y] : cnt)
            if (y & 1)
            {
                odd++;
                fuck |= !sym[x];
            }
        Hash_Tree[child] = ++edge_cnt;
        sym[edge_cnt] = odd < 2 && !fuck;
    }
    return Hash_Tree[child];
}

void solve()
{
    int n;
    cin >> n;
    Hash_Tree.clear();
    sym.clear();
    Hash_Tree[vector<int>(0)] = 0;
    sym[0] = true;
    edge_cnt = 0;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout << (sym[dfs(1, 0, g)] ? "YES" : "NO") << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    // int T;
    // cin >> T;
    // while (T--)
    solve();
    return 0;
}
