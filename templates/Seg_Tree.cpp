#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
int ar[N];
struct Seg_Tree
{
    long long val[N << 2], ls[N << 2], rs[N << 2], lazy[N << 2];
    // sum Tree
    void build(int l, int r, int p)
    {
        ls[p] = l;
        rs[p] = r;
        if (l == r)
        {
            val[p] = ar[l];
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        val[p] = val[p << 1] + val[p << 1 | 1];
    }
    void pushdown(int p)
    {
        if (ls[p] == rs[p])
            return;
        int mid = ls[p] + rs[p] >> 1;
        val[p << 1] += lazy[p] * (rs[p << 1] - ls[p << 1] + 1);
        val[p << 1 | 1] += lazy[p] * (rs[p << 1 | 1] - ls[p << 1 | 1] + 1);
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
    }
    void update(int l, int r, int x, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
        {
            val[p] += (rs[p] - ls[p] + 1) * x;
            lazy[p] += x;
            return;
        }
        if (lazy[p])
            pushdown(p);
        int mid = ls[p] + rs[p] >> 1;
        if (l <= mid)
            update(l, r, x, p << 1);
        if (r > mid)
            update(l, r, x, p << 1 | 1);
        val[p] = val[p << 1] + val[p << 1 | 1];
    }
    long long query(int l, int r, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
        {
            return val[p];
        }
        if (lazy[p])
            pushdown(p);
        long long mid = ls[p] + rs[p] >> 1, res = 0;
        if (l <= mid)
            res += query(l, r, p << 1);
        if (r > mid)
            res += query(l, r, p << 1 | 1);
        return res;
    }
} ST;
struct Seg_Tree2
{
    long long val[N << 2], ls[N << 2], rs[N << 2], lazy1[N << 2], lazy2[N << 2], P;
    // SumTree lazy1 mul,lazy2 add
    void build(int l, int r, int p)
    {
        ls[p] = l;
        rs[p] = r;
        if (l == r)
        {
            val[p] = ar[l] % P;
            return;
        }
        lazy1[p] = 1;
        lazy2[p] = 0;
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        val[p] = (val[p << 1] + val[p << 1 | 1]) % P;
    }
    void pushdown(int p)
    {
        int mid = ls[p] + rs[p] >> 1;
        val[p << 1] = (lazy1[p] * val[p << 1] + lazy2[p] * (mid - ls[p] + 1)) % P;
        val[p << 1 | 1] = (lazy1[p] * val[p << 1 | 1] + lazy2[p] * (rs[p] - mid)) % P;
        lazy1[p << 1] = lazy1[p] * lazy1[p << 1] % P;
        lazy1[p << 1 | 1] = lazy1[p] * lazy1[p << 1 | 1] % P;
        lazy2[p << 1] = (lazy1[p] * lazy2[p << 1] + lazy2[p]) % P;
        lazy2[p << 1 | 1] = (lazy1[p] * lazy2[p << 1 | 1] + lazy2[p]) % P;
        lazy1[p] = 1;
        lazy2[p] = 0;
        return;
    }
    void update1(int l, int r, long long x, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
        {
            val[p] = val[p] * x % P;
            lazy1[p] = lazy1[p] * x % P;
            lazy2[p] = lazy2[p] * x % P;
            return;
        }
        if (lazy2[p] || lazy1[p] != 1)
            pushdown(p);
        int mid = ls[p] + rs[p] >> 1;
        if (l <= mid)
            update1(l, r, x, p << 1);
        if (r > mid)
            update1(l, r, x, p << 1 | 1);
        val[p] = (val[p << 1] + val[p << 1 | 1]) % P;
    }
    void update2(int l, int r, long long x, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
        {
            val[p] = (val[p] + (rs[p] - ls[p] + 1) * x) % P;
            lazy2[p] = (lazy2[p] + x) % P;
            return;
        }
        if (lazy2[p] || lazy1[p] != 1)
            pushdown(p);
        int mid = ls[p] + rs[p] >> 1;
        if (l <= mid)
            update2(l, r, x, p << 1);
        if (r > mid)
            update2(l, r, x, p << 1 | 1);
        val[p] = (val[p << 1] + val[p << 1 | 1]) % P;
    }
    long long query(int l, int r, int p)
    {
        if (l <= ls[p] && rs[p] <= r)
            return val[p];
        pushdown(p);
        long long mid = ls[p] + rs[p] >> 1, res = 0;
        if (l <= mid)
            res += query(l, r, p << 1);
        if (r > mid)
            res += query(l, r, p << 1 | 1);
        return res % P;
    }
} ST2;
// luogu P2572 good problem
struct seg_tree3
{
    int sum[N << 2][2], lval[N << 2][2], rval[N << 2][2], conval[N << 2][2];
    int L[N << 2], R[N << 2], lazy[N << 2][2];
    void pushup(int p)
    {
        for (int i = 0; i < 2; i++)
        {
            sum[p][i] = sum[p << 1][i] + sum[p << 1 | 1][i];
            lval[p][i] = lval[p << 1][i] == R[p << 1] - L[p << 1] + 1 ? lval[p << 1][i] + lval[p << 1 | 1][i] : lval[p << 1][i];
            rval[p][i] = rval[p << 1 | 1][i] == R[p << 1 | 1] - L[p << 1 | 1] + 1 ? rval[p << 1 | 1][i] + rval[p << 1][i] : rval[p << 1 | 1][i];
            conval[p][i] = max(max(conval[p << 1][i], conval[p << 1 | 1][i]), rval[p << 1][i] + lval[p << 1 | 1][i]);
        }
    }
    void fun(int p, int op)
    {
        if (op == 0)
        {
            int len = R[p] - L[p] + 1;
            lval[p][0] = rval[p][0] = conval[p][0] = sum[p][0] = len;
            lval[p][1] = rval[p][1] = conval[p][1] = sum[p][1] = 0;
            lazy[p][0] = 0;
            lazy[p][1] = 0;
        }
        else if (op == 1)
        {
            int len = R[p] - L[p] + 1;
            lval[p][0] = rval[p][0] = conval[p][0] = sum[p][0] = 0;
            lval[p][1] = rval[p][1] = conval[p][1] = sum[p][1] = len;
            lazy[p][0] = 1;
            lazy[p][1] = 0;
        }
        else
        {
            swap(lval[p][0], lval[p][1]);
            swap(rval[p][0], rval[p][1]);
            swap(conval[p][0], conval[p][1]);
            swap(sum[p][0], sum[p][1]);
            lazy[p][1] ^= 1;
        }
    }
    void pushdown(int p)
    {
        if (L[p] == R[p])
            return;
        if (lazy[p][0] != -1)
        {
            fun(p << 1, lazy[p][0]);
            fun(p << 1 | 1, lazy[p][0]);
        }
        if (lazy[p][1])
        {
            fun(p << 1, 2);
            fun(p << 1 | 1, 2);
        }
        lazy[p][0] = -1;
        lazy[p][1] = 0;
    }
    void build(int l, int r, int p)
    {
        L[p] = l;
        R[p] = r;
        lazy[p][0] = -1;
        lazy[p][1] = 0;
        if (l == r)
        {
            int op;
            cin >> op;
            sum[p][op] = lval[p][op] = rval[p][op] = conval[p][op] = 1;
            sum[p][op ^ 1] = lval[p][op ^ 1] = rval[p][op ^ 1] = conval[p][op ^ 1] = 0;
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        pushup(p);
    }
    void update(int l, int r, int op, int p)
    {
        if (l <= L[p] && R[p] <= r)
        {
            fun(p, op);
            return;
        }
        pushdown(p);
        int mid = L[p] + R[p] >> 1;
        if (l <= mid)
            update(l, r, op, p << 1);
        if (r > mid)
            update(l, r, op, p << 1 | 1);
        pushup(p);
    }
    int query_sum(int l, int r, int p)
    {
        if (l <= L[p] && R[p] <= r)
        {
            return sum[p][1];
        }
        pushdown(p);
        int mid = L[p] + R[p] >> 1, res = 0;
        if (l <= mid)
            res += query_sum(l, r, p << 1);
        if (r > mid)
            res += query_sum(l, r, p << 1 | 1);
        return res;
    }
    int query_con(int l, int r, int p)
    {
        if (l <= L[p] && R[p] <= r)
        {
            return conval[p][1];
        }
        pushdown(p);
        int mid = L[p] + R[p] >> 1, lres = 0, rres = 0, res = 0;
        if (l <= mid)
            lres = query_con(l, r, p << 1);
        if (r > mid)
            rres += query_con(l, r, p << 1 | 1);
        res = max(lres, rres);
        if (L[p] != R[p])
            res = max(res, min(mid - l + 1, rval[p << 1][1]) + min(r - mid, lval[p << 1 | 1][1]));
        return res;
    }
} ST33;
struct info
{
    int val;
    info() : val(INT32_MIN) {}
    info(int x) : val(x) {}
    info &operator+=(int x)
    {
        val += x;
        return *this;
    }
};
info operator+(const info &a, const info &b)
{
    info res;
    res.val = max(a.val, b.val);
    return res;
}
template <class T>
struct segment_tree_template
{
    T val[N << 2];
    int L[N << 2], R[N << 2];
    int lazy[N << 2];
    void operate(int x, int p) { val[p] += x, lazy[p] += x; }
    void pushup(int p) { val[p] = val[p << 1] + val[p << 1 | 1]; }
    void pushdown(int p)
    {
        if (L[p] == R[p])
        {
            lazy[p] = 0;
            return;
        }
        operate(lazy[p], p << 1);
        operate(lazy[p], p << 1 | 1);
        lazy[p] = 0;
    }
    void build(int l, int r, int p = 1)
    {
        L[p] = l;
        R[p] = r;
        if (l == r)
        {
            // initialize here
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        pushup(p);
    }
    void update(int l, int r, int w, int p = 1)
    {
        if (l <= L[p] && R[p] <= r)
        {
            operate(w, p);
            return;
        }
        if (lazy[p])
            pushdown(p);
        int mid = L[p] + R[p] >> 1;
        if (l <= mid)
            update(l, r, w, p << 1);
        if (r > mid)
            update(l, r, w, p << 1 | 1);
        pushup(p);
    }
    T query(int l, int r, int p = 1)
    {
        if (l <= L[p] && R[p] <= r)
            return val[p];
        if (lazy[p])
            pushdown(p);
        int mid = L[p] + R[p] >> 1;
        T res;
        if (l <= mid)
            res = query(l, r, p << 1) + res;
        if (r > mid)
            res = res + query(l, r, p << 1 | 1);
        return res;
    }
};
segment_tree_template<info> STT;

struct info
{
    int val, Lson, Rson;
    info() : val(0), Lson(0), Rson(0) {}
    info(int x) : val(x), Lson(0), Rson(0) {}
};

struct Seg_Tree_Sus
{
    info val[N << 2];
    int L[N << 2], R[N << 2];
    int nodecnt;
    int build(int l, int r)
    {
        int p = ++nodecnt;
        L[p] = l;
        R[p] = r;
        if (l == r)
        {
            int x;
            cin >> x;
            val[p] = x;
            return;
        }
        int mid = l + r >> 1;
        val[p].Lson = build(l, mid);
        val[p].Rson = build(mid + 1, r);
        return p;
    }
    int newnode(int p)
    {
        val[++nodecnt] = val[p];
        return nodecnt;
    }
    int update(int x, int w, int p)
    {
        p = newnode(p);
        if (L[p] == R[p])
        {
            val[p] = w;
            return;
        }
        int mid = L[p] + R[p] >> 1;
        if (x <= mid)
            val[p].Lson = update(x, w, val[p].Lson);
        else
            val[p].Rson = update(x, w, val[p].Rson);
        return p;
    }
    info query(int x,int p)
    {
        if (L[p] == R[p])
        {
            return val[p];
        }
        int mid = L[p] + R[p] >> 1;
        if (x <= mid)
            return query(x,val[p].Lson);
        else
            return query(x,val[p].Rson);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}