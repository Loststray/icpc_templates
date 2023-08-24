#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
const uint64_t mod1 = 19260817;
const uint64_t mod2 = 1e9 + 7;
const uint64_t base = 26;
uint64_t myhash(const string &a)
{
    uint64_t res = 0;
    for (const auto &it : a)
        res = (res * base + (it - 'a')) % mod1;
    return res;
}
uint64_t myhash_1(const string &a)
{
    uint64_t res = 0;
    for (const auto &it : a)
        res = (res * base + (it - 'a')) % mod2;
    return res;
}
void solve()
{
    int n;
    cin >> n;
    vector<pair<uint64_t, uint64_t>> ar;
    for (int i = 1; i <= n; i++)
    {
        string tmp;
        cin >> tmp;
        ar.push_back({myhash(tmp), myhash_1(tmp)});
    }
    sort(ar.begin(), ar.end());
    auto res = unique(ar.begin(), ar.end()) - ar.begin();
    cout << res << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}