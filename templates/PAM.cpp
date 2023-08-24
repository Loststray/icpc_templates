#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 7;
const int sigma = 26;
namespace pam
{
    int sz, tot, last;
    int ch[N][sigma], len[N], fail[N];
    int cnt[N], dep[N], dif[N], slink[N];
    char s[N];
    int node(int l)
    {
        sz++;
        memset(ch[sz], 0, sizeof(ch[sz]));
        len[sz] = l;
        fail[sz] = 0;
        cnt[sz] = 0;
        dep[sz] = 0;
        return sz;
    }
    void clear()
    {
        sz = -1;
        last = 0;
        s[tot = 0] = '$';
        node(0);
        node(-1);
        fail[0] = 1;
    }
    int getfail(int x)
    {
        while (s[tot - len[x] - 1] != s[tot])
            x = fail[x];
        return x;
    }
    void insert(char c)
    {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a'])
        {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;
            dif[x] = len[x] - len[fail[x]];
            if (dif[x] == dif[fail[x]])
                slink[x] = slink[fail[x]];
            else
                slink[x] = fail[x];
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
}
using pam::dif;
using pam::fail;
using pam::len;
using pam::slink;
void solve()
{
    string str;
    while (str.empty())
        getline(cin, str);
    pam::clear();
    const int n = str.size();
    vector<int> dp(n + 1, INT32_MAX / 2);
    str = '!' + str;
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        pam::insert(str[i]);
        for (int x = pam::last; len[x]; x = fail[x])
        {
            dp[i] = min(dp[i], dp[i - len[x]] + 1);
        }
    }
    cout << n - dp[n] << '\n';
}
int main()
{
    freopen("String1.in", "r", stdin);
    freopen("String1.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}