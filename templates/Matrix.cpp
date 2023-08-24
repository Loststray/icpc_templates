#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
struct mat
{
    static const int sz{11};
    int g[sz][sz];
    static const int getter() { return sz; }
    auto &operator[](int x) { return g[x]; }
    auto &operator[](int x) const { return g[x]; }
    mat operator*(const mat &b) const
    {
        mat res;
        for (int i = 0; i < sz; i++)
            for (int k = 0; k < sz; k++)
            {
                auto tmp = g[i][k];
                for (int j = 0; j < sz; j++)
                {
                    res[i][j] += b[k][j] * tmp;
                }
            }
        return res;
    }
    mat &operator*=(const mat &b)
    {
        mat res;
        for (int i = 0; i < sz; i++)
            for (int k = 0; k < sz; k++)
            {
                auto tmp = g[i][k];
                for (int j = 0; j < sz; j++)
                {
                    res[i][j] += b[k][j] * tmp;
                }
            }
        *this = move(res);
        return *this;
    }
    mat operator+(const mat &b) const
    {
        mat res;
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                res[i][j] = (g[i][j] + b[i][j]);
        return res;
    }
    mat &operator+=(const mat &b)
    {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                (g[i][j] += b[i][j]);
        return *this;
    }
    mat operator-(const mat &b) const
    {
        mat res;
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                res[i][j] = (g[i][j] - b[i][j]);
        return res;
    }
    mat &operator-=(const mat &b)
    {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                (g[i][j] -= b[i][j]);
        return *this;
    }
    void neutralize()
    {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                g[i][j] = i == j;
    }
    bool unit()
    {
        bool f = 1;
        for (int i = 0; i < sz && f; i++)
            for (int j = 0; j < sz && f; j++)
                if (i == j && g[i][j] != 1 || i != j && g[i][j] != 0)
                    f = 0;
        return f;
    }
};
mat qpower(mat a, long long b)
{
    mat res;
    res.neutralize();
    while (b > 0)
    {
        if (b & 1)
            res *= a;
        a *= a;
        b >>= 1ll;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    mat a(2), b(2);
    a[0][0] = a[0][1] = a[1][0] = a[1][1] = 1;
    b[0][0] = b[0][1] = b[1][0] = 1;
    cout << (a * qpower(b, n - 2))[0][0] << '\n';
}
