#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 7;
struct Trie
{
    int tot, nxt[N][63], cnt[N];
    void clear()
    {
        for (int i = 0; i <= tot; i++)
        {
            cnt[i] = 0;
            for (int j = 0; j <= 62; j++)
                nxt[i][j] = 0;
        }
        tot = 0;
    }
    int geths(char a)
    {
        if (a >= '0' && a <= '9')
            return a - '0';
        if (a >= 'A' && a <= 'Z')
            return a - 'A' + 10;
        if (a >= 'a' && a <= 'z')
            return a - 'a' + 36;
        return 0;
    }
    void insert(char *a)
    {
        int pos = 0, len = strlen(a);
        for (int i = 0; i < len; i++)
        {
            int c = geths(a[i]);
            if (!nxt[pos][c])
                nxt[pos][c] = ++tot;
            pos = nxt[pos][c];
            cnt[pos]++;
        }
    }
    int query(char *a)
    {
        int pos = 0, len = strlen(a);
        for (int i = 0; i < len; i++)
        {
            int c = geths(a[i]);
            if (!nxt[pos][c])
                return 0;
            pos = nxt[pos][c];
        }
        return cnt[pos];
    }
} t;
struct P_trie
{
    static constexpr int sigma = 20;
    int nxt[N * (sigma + 2)][2];
    int tot = 0, res = 0;
    int insert(int x, int val)
    {
        int rt = ++tot;
        int p = tot;
        for (int i = sigma - 1; i >= 0; i--)
        {
            int to = (val >> i) & 1;
            nxt[p][0] = nxt[x][0];
            nxt[p][1] = nxt[x][1];
            p = nxt[p][to] = ++tot;
            x = nxt[x][to];
        }
        if (!x)
            res++;
        return rt;
    }
} pt;
int main()
{
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--)
    {
        t.clear();
        int n, q;
        cin >> n >> q;
        char tmp[114514];
        for (int i = 0; i < n; i++)
        {
            cin >> tmp;
            t.insert(tmp);
        }
        for (int i = 0; i < q; i++)
        {
            cin >> tmp;
            cout << t.query(tmp) << '\n';
        }
    }
}