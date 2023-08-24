#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
template<typename T>
class Point
{
public:
    T x,y;
    Point() : x(0),y(0) {}
    Point(T a,T b) : x(a),y(b) {}
    Point operator+ (const Point& a) const { return {x + a.x , y + a.y}; }
    Point operator- (const Point& a) const { return {x - a.x , y - a.y}; }
    T operator* (const Point& a) const { return x * a.y - y * a.x; }
    T operator^ (const Point& a) const { return x * a.x + y * a.y; }
    Point operator* (T p) const { return {x * p,y * p}; }
    Point operator/ (T p) const { return {x / p,y / p}; }
    friend istream& operator>> (istream& in,Point & a) { return in >> a.x >> a.y; }
};
using poi = Point<double>;
template<typename T>
class Line
{
public:
    Point<T> p,v;
    double angle;
    void calc() { angle = atan(v.y,v.x); }
    Line(){};
    Line(Point<T>& a,Point<T>& b) : p(a),v(b) { angle = calc();}
};
void solve()
{

}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}