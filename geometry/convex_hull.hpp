#include <bits/stdc++.h>
using namespace std;

#include "point.hpp"

void build_convex_hull(vector<point> &points, bool include_collinear = false) {
    point p0 = *min_element(points.begin(), points.end(), 
        [&](point a, point b) {
            return make_pair(a.y, a.x) < make_pair(b.y, b.x);
        });
    sort(points.begin(), points.end(), 
        [&](point a, point b){
            int o = orientation(p0, a, b);
            if(o == 0) 
                return norm(a - p0) < norm(b - p0);
            return o < 0;
        });

    if (include_collinear) {
        int i = (int)points.size()-1;
        while (i >= 0 && collinear(p0, points[i], points.back())) i--;
        reverse(points.begin()+i+1, points.end());
    }

    vector<point> st;
    for(int i = 0; i < int(points.size()); i++) {
        while(st.size() > 1 && !cw(st[st.size()-2], st[st.size()-1], points[i], include_collinear))
            st.pop_back();
        st.push_back(points[i]);
    }
    points = st;
}
