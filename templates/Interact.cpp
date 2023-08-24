#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 64;
const int P = 1e9 + 7;

int ask(int l, int r)
{
    if (r <= l)
        return 0;
    cout << "? " << l << ' ' << r << endl;
    int x;
    cin >> x;
    return x;
}

int dfs(int l, int r)
{
    if (l == r)
        return l;
    int mid = l + r >> 1;
    int idl = dfs(l, mid), idr = dfs(mid + 1, r);
    if (ask(idl, idr) == ask(idl, idr - 1))
        return idr;
    return idl;
}

void solve()
{
    int n;
    cin >> n;
    auto res = dfs(1,n);
    cout << "! " << res << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
