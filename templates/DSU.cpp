#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
struct DSU
{
    vector<int> par, sz;
    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    bool is_same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return 0;
        if (sz[x] < sz[y])
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return 1;
    }
    int size(int x) { return sz[find(x)]; }
};
void solve()
{
    
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}