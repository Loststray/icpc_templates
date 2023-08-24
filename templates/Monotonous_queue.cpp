#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
const int P = 998244353;
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> ar(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> ar[i];
    deque<pair<int, int>> qmin, qmax;
    for (int i = 1; i <= n; i++)
    {
        while (!qmin.empty() && qmin.back().second >= ar[i])
            qmin.pop_back();
        while (!qmin.empty() && i - qmin.front().first >= k)
            qmin.pop_front();
        qmin.push_back(make_pair(i, ar[i]));
        if (i >= k)
            cout << qmin.front().second << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++)
    {
        while (!qmax.empty() && qmax.back().second <= ar[i])
            qmax.pop_back();
        while (!qmax.empty() && i - qmax.front().first >= k)
            qmax.pop_front();
        qmax.push_back(make_pair(i, ar[i]));
        if (i >= k)
            cout << qmax.front().second << ' ';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // int T;
    // cin >> T;
    // while (T--)
    solve();
    return 0;
}