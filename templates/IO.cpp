#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 7;
namespace io
{
    const int BUFSIZE = 1 << 20;
    char ibuf[BUFSIZE], *is = ibuf, *it = ibuf;
    char obuf[BUFSIZE], *os = obuf, *ot = obuf + BUFSIZE;
    char getch()
    {
        if (is == it)
            it = (is = ibuf) + fread(ibuf, 1, BUFSIZE, stdin);
        return (is == it) ? EOF : *is++;
    }
    long long read()
    {
        long long res = 0;
        bool neg = false;
        char ch = getch();
        while (!(isdigit(ch) or ch == '-') and ch != EOF)
            ch = getch();
        if (ch == '-')
            neg = true, ch = getch();
        while (isdigit(ch))
            res = res * 10 + (ch - '0'), ch = getch();
        return neg ? -res : res;
    }
    void flush()
    {
        fwrite(obuf, 1, os - obuf, stdout);
        os = obuf;
    }
    void putch(char ch)
    {
        *os++ = ch;
        if (os == ot)
            flush();
    }
    template <class T>
    void print(T res)
    {
        char q[64];
        int top;
        if (res < 0)
            putch('-'), res = -res;
        if (res == 0)
            putch('0');
        top = 0;
        while (res)
            q[top++] = res % 10 + '0', res /= 10;
        while (top--)
            putch(q[top]);
    }
    double getreal()
    {
        double res = 0, base;
        bool neg = false;
        char ch = getch();
        while (!(isdigit(ch) or ch == '-') and ch != EOF)
            ch = getch();
        if (ch == '-')
            neg = true, ch = getch();
        while (isdigit(ch))
            res = res * 10.0 + (ch - '0'), ch = getch();
        if (ch == '.')
        {
            base = 0.1;
            ch = getch();
            while (isdigit(ch))
                res += (ch - '0') * base, base *= 0.1, ch = getch();
        }
        return neg ? -res : res;
    }
    void putreal(double res, int acc = 0)
    {
        int who;
        double tmp, base = 1.0;
        if (res < 0)
            putch('-'), res = -res;
        tmp = res - (int)(res);
        for (int i = 1; i <= acc + 1; ++i)
            base /= 10.0, who = tmp / base, tmp -= who * base;
        if (who >= 5)
            res += base * 10.0;
        base = 1.0;
        while (res / base >= 10.0)
            base *= 10.0;
        while (base >= 1.0)
            who = res / base, putch(who + '0'), res -= who * base, base /= 10.0;
        if (acc)
        {
            putch('.');
            base = 0.1;
            while (acc--)
                who = res / base, putch(who + '0'), res -= who * base, base /= 10.0;
        }
    }
    template <class T>
    void read(T &a)
    {
        a = 0;
        bool neg = false;
        char ch = getch();
        while (!(isdigit(ch) or ch == '-') and ch != EOF)
            ch = getch();
        if (ch == '-')
            neg = true, ch = getch();
        while (isdigit(ch))
            a = a * 10 + (ch - '0'), ch = getch();
        if (neg)
            a = -a;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
}