#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;

class Splay
{
private:
    int root, tot;
    vector<int> par, ch[2], val, cnt, sz;
    void maintain(int x) { sz[x] = sz[ch[0][x]] + sz[ch[1][x]] + cnt[x]; }
    // is right?
    bool get(int x) { return x == ch[1][par[x]]; }
    void del_node(int x) { ch[0][x] = ch[1][x] = par[x] = val[x] = sz[x] = cnt[x] = 0; }
    void rotate(int x)
    {
        int y = par[x], z = par[par[x]];
        bool check = get(x); // l = 0 , r = 1;
        int &childx = ch[check ^ 1][x];
        ch[check][y] = childx;
        if (childx)
            par[childx] = y;
        childx = y;
        par[y] = x;
        par[x] = z;
        if (z)
            ch[y == ch[1][z]][z] = x;
        maintain(x);
        maintain(y);
    }
    void zig_zag_wow(int x)
    {
        for (int f = par[x]; f = par[x], f; rotate(x))
            if (par[f])
                rotate(get(x) == get(f) ? f : x);
        root = x;
    }

public:
    Splay(int n)
    {
        par.resize(n + 1);
        ch[0].resize(n + 1);
        ch[1].resize(n + 1);
        val.resize(n + 1);
        cnt.resize(n + 1);
        sz.resize(n + 1);
        root = 0;
        tot = 0;
    }
    void insert(int x)
    {
        if (!root)
        {
            val[++tot] = x;
            cnt[tot]++;
            root = tot;
            maintain(root);
            return;
        }
        int cur = root, pa = 0;
        while (1)
        {
            if (val[cur] == x)
            {
                cnt[cur]++;
                maintain(cur);
                maintain(pa);
                zig_zag_wow(cur);
                return;
            }
            pa = cur;
            cur = ch[val[cur] < x][cur];
            if (!cur)
            {
                val[++tot] = x;
                cnt[tot]++;
                par[tot] = pa;
                ch[val[pa] < x][pa] = tot;
                maintain(tot);
                maintain(pa);
                zig_zag_wow(tot);
                return;
            }
        }
    }
    int get_rank(int x)
    {
        int ans = 0, cur = root;
        while (1)
        {
            if (x < val[cur])
                cur = ch[0][cur];
            else
            {
                ans += sz[ch[0][cur]];
                if (x == val[cur])
                {
                    zig_zag_wow(cur);
                    return ans + 1;
                }
                ans += cnt[cur];
                cur = ch[1][cur];
            }
        }
    }
    int get_xth(int x)
    {
        int cur = root;
        while (1)
        {
            if (ch[0][cur] && x <= sz[ch[0][cur]])
                cur = ch[0][cur];
            else
            {
                x -= cnt[cur] + sz[ch[0][cur]];
                if (x <= 0)
                {
                    zig_zag_wow(cur);
                    return val[cur];
                }
                cur = ch[1][cur];
            }
        }
    }
    int pre()
    {
        int cur = ch[0][root];
        if (!cur)
            return cur;
        while (ch[1][cur])
            cur = ch[1][cur];
        zig_zag_wow(cur);
        return cur;
    }
    int pre(bool flag)
    {
        int cur = ch[0][root];
        if (!cur)
            return cur;
        while (ch[1][cur])
            cur = ch[1][cur];
        zig_zag_wow(cur);
        return val[cur];
    }
    int nxt()
    {
        int cur = ch[1][root];
        if (!cur)
            return cur;
        while (ch[0][cur])
            cur = ch[0][cur];
        zig_zag_wow(cur);
        return cur;
    }
    int nxt(bool flag)
    {
        int cur = ch[1][root];
        if (!cur)
            return cur;
        while (ch[0][cur])
            cur = ch[0][cur];
        zig_zag_wow(cur);
        return val[cur];
    }
    void erase(int x)
    {
        get_rank(x);
        if (cnt[root] > 1)
        {
            cnt[root]--;
            maintain(root);
            return;
        }
        if (!ch[1][root] && !ch[0][root])
        {
            del_node(root);
            root = 0;
            return;
        }
        if (!ch[0][root])
        {
            int cur = root;
            root = ch[1][root];
            par[root] = 0;
            del_node(cur);
            return;
        }
        if (!ch[1][root])
        {
            int cur = root;
            root = ch[0][root];
            par[root] = 0;
            del_node(cur);
            return;
        }
        else
        {
            int cur = root;
            int prenode = pre();
            par[ch[1][cur]] = prenode;
            ch[1][prenode] = ch[1][cur];
            del_node(cur);
            maintain(root);
            return;
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    Splay wow(n + 1);
    while (n--)
    {
        int op, x;
        cin >> op >> x;
        switch (op)
        {
        case 1:
            wow.insert(x);
            break;
        case 2:
            wow.erase(x);
            break;
        case 3:
            cout << wow.get_rank(x) << '\n';
            break;
        case 4:
            cout << wow.get_xth(x) << '\n';
            break;
        case 5:
            wow.insert(x);
            cout << wow.pre(1) << '\n';
            wow.erase(x);
            break;
        case 6:
            wow.insert(x);
            cout << wow.nxt(1) << '\n';
            wow.erase(x);
            break;
        default:
            // what;
            break;
        }
    }
    return;
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