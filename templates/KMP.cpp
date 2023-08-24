#include <bits/stdc++.h>
using namespace std;
string text, pat;
void get_nxt(const string &s, vector<int> &nxt)
{
    const int n = s.size();
    nxt.resize(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int j = nxt[i - 1];
        while (j && s[i] != s[j + 1])
            j = nxt[j];
        if (s[i] == s[j + 1])
            j++;
        nxt[i] = j;
    }
}
void prefix_function(string &s, vector<int> &pi)
{
    int n = (int)s.length();
    pi.clear();
    pi.resize(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}
void find_occurrences(string &text, string &pattern, vector<int> &pos)
{
    string cur = pattern + '#' + text;
    int sz1 = text.size(), sz2 = pattern.size();
    vector<int> nxt;
    prefix_function(cur, nxt);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++)
        if (nxt[i] == sz2)
            pos.push_back(i - sz2 + 1);
}
void solve()
{
    vector<int> pos;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> pat >> text)
        solve();
    return 0;
}