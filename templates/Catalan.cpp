#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-5;
typedef pair<int, int> poi;
vector<vector<int>> catalan(105);
vector<int> fuckingmul(vector<int> a, vector<int> b)
{
    vector<int> tmp(a.size() + b.size(), 0);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            tmp[i + j] += a[i] * b[j];
            tmp[i + j + 1] += tmp[i + j] / 10;
            tmp[i + j] %= 10;
        }
    }
    while (tmp.back() == 0)
        tmp.pop_back();

    return tmp;
}
vector<int> fuckingadd(vector<int> a, vector<int> b)
{
    int sz = max(a.size(), b.size());
    while (a.size() < b.size())
        a.emplace_back(0);
    while (a.size() > b.size())
        b.emplace_back(0);
    vector<int> tmp(sz + 1, 0);
    for (int i = 0; i < sz; i++)
    {
        tmp[i] += a[i] + b[i];
        tmp[i + 1] += tmp[i] / 10;
        tmp[i] %= 10;
    }
    if (!tmp.back())
        tmp.pop_back();
    return tmp;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, cnt = 0;
    catalan[0] = catalan[1] = {1};
    for (int i = 2; i <= 100; i++)
    {
        catalan[i] = {0};
        for (int j = 0; j < i; j++)
            catalan[i] = fuckingadd(catalan[i], fuckingmul(catalan[j], catalan[i - j - 1]));
    }
    while (cin >> n && ~n)
    {
        cout << ++cnt << ' ' << n << ' ';
        catalan[n] = fuckingmul(catalan[n], {2});
        for (auto it = catalan[n].rbegin(); it != catalan[n].rend(); it++)
            cout << *it;
        cout << '\n';
    }
    return 0;
}