#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
uniform_real_distribution<double> dist(0, 1);
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
array<array<int, 3>, N> friends;
int pos[N];
const double temperture_start = 1e10;
const double temperture_final = 1e-12;
const double cooling_factor = 0.996;
const int final_iteration_times = 5000;
int n;
int ans;
int calc()
{
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (auto it : friends[i])
            res += abs(pos[i] - pos[it]);
    return res;
}
void simulate_anneal()
{
    double t = temperture_start;
    uniform_int_distribution<int> tmp(1, n);
    while (t > temperture_final)
    {
        int x = tmp(rnd), y = tmp(rnd);
        while (x == y)
            x = tmp(rnd), y = tmp(rnd);
        swap(pos[x], pos[y]);
        auto delta = ans - calc();
        if (delta > 0)
            ans -= delta;
        else if (exp(delta / t) > dist(rnd))
            swap(pos[x], pos[y]);
        t *= cooling_factor;
    }
}
void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> friends[i][j];
        pos[i] = i;
    }
    ans = calc();
    simulate_anneal();
    cout << ans / 2;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);
    solve();
    return 0;
}