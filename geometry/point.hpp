#include <bits/stdc++.h>
using namespace std;

using dist_t = long double;

struct point {
    int64_t x, y;

    point() : x(0), y(0) {}
    point(int64_t _x, int64_t _y) : x(_x), y(_y) {}

    point& operator+=(const point &other) { x += other.x, y += other.y; return *this; }
    point& operator-=(const point &other) { x -= other.x, y -= other.y; return *this; }
    point& operator*=(int64_t mult) { x *= mult, y *= mult; return *this; }
    point& operator/=(int64_t div) { x /= div, y /= div; return *this; }

    point operator+(const point &other) const { return point(*this) += other; }
    point operator-(const point &other) const { return point(*this) -= other; }
    point operator*(int64_t mult) const { return point(*this) *= mult; }
    point operator/(int64_t div) const { return point(*this) /= div; }

    bool operator==(const point &other) const { return x == other.x && y == other.y; }
    bool operator!=(const point &other) const { return !(*this == other); }

    point operator-() const { return point(-x, -y); }
    point rotate90() const { return point(-y, x); }

    friend ostream& operator<<(ostream &os, const point &p) {
        return os << '(' << p.x << ", " << p.y << ')';
    }

};

// dot product, norm (length^2), abs (length)
int64_t dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

int64_t norm(point a) {
    return dot(a, a);
}

dist_t abs(point a) {
    return sqrt(norm(a));
}

int64_t det(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

double angle(point a, point b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

dist_t euclidean_distance(point a, point b) {
    return abs(a - b);
}

int64_t manhattan_distance(point a, point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}


int orientation(point a, point b, point c) {
   int64_t v = det(b - a, c - a); // = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
   if(v > 0) return +1; // counter-clockwise
   if(v < 0) return -1; // clockwise
   return 0; // collinear 
}

bool collinear(point a, point b, point c) { return orientation(a, b, c) == 0; }

// is_clockwise
bool cw(point a, point b, point c, bool include_collinear = false) {
    int o = orientation(a, b, c);
    return o < 0 || o == 0 && include_collinear;
}