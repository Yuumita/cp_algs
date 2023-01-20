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

// is clockwise
bool cw(point a, point b, point c, bool include_collinear = false) {
    int o = orientation(a, b, c);
    return o < 0 || o == 0 && include_collinear;
}

void build_convex_hull(vector<point> &points, bool include_collinear = false) {
    point p0 = *min_element(points.begin(), points.end(), 
        [&](point a, point b) {
            return make_pair(a.y, a.x) < make_pair(b.y, b.x);
        });
    sort(points.begin(), points.end(), 
        [&](point a, point b){
            int o = orientation(a, b);
            if(o == 0) 
                return norm(a - p0) < norm(b - p0);
            return o < 0;
        });

    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<point> st;
    for(int i = 0; i < int(points.size()); i++) {
        while(st.size() > 1 && !cw(st[st.size()-2], st[st.size()-1], points[i], include_collinear))
            st.pop_back();
        st.push_back(points[i]);
    }
    points = st;
}


 
int main(){
}