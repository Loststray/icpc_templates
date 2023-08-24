#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
const int M = 2e5 + 7;
const double eps = 1e-5;
struct info
{
    int val;
    info() : val(0) {}
    info(int x) : val(x) {}
    friend istream &operator>>(istream &in, info &x)
    {
        return in >> x.val;
    }
    friend ostream &operator<<(ostream &out, const info &x)
    {
        return out << x.val;
    }
};
info operator+(const info &a, const info &b)
{
    info res;
    res.val = max(a.val, b.val);
    return res;
}
struct sparse_table
{
    static int lg[N];
    static void init()
    {
        for (int i = 2; i < N; i++)
            lg[i] = lg[i >> 1] + 1;
    }
    vector<array<info, 32>> val;
    sparse_table(int n) : val(n) {}
    sparse_table() {}
    info &operator[](int x) { return val[x][0]; }
    const info operator[](int x) const { return val[x][0]; }
    void build()
    {
        const int n = val.size() - 1, len = lg[n];
        for (int i = 1; i <= len; i++)
            for (int l = 1; l + (1 << i) - 1 <= n; l++)
                val[l][i] = val[l][i - 1] + val[l + (1 << i - 1)][i - 1];
    }
    info query(int l, int r)
    {
        const int dep = lg[r - l + 1];
        return val[l][dep] + val[r - (1 << dep) + 1][dep];
    }
};
int sparse_table::lg[N] = {0};

void solve()
{
    int n, m;
    cin >> n >> m;
    sparse_table st(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> st[i];
    st.build();
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.in", "r+", stdin);
    freopen("data.out", "w+", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sparse_table::init();
    solve();
    return 0;
}