#include "utils.h"

/*
Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).

Return true if all the rectangles together form an exact cover of a rectangular region.

Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
Output: true

Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
Output: false

Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
Output: false

*/

struct Point {
    int x = 0, y = 0;

    Point() = default;
    Point(int x_, int y_)
        : x(x_), y(y_)
    { }

    friend bool operator< (const Point& pt1, const Point& pt2)
    {
        if (pt1.x != pt2.x) return pt1.x < pt2.x;
        return pt1.y < pt2.y;
    }
};

struct Rect {
    Point bl;  // bottom-left corner
    Point tr;  // top-right corner

    Rect()
        : bl(INT_MAX, INT_MAX)
        , tr(INT_MIN, INT_MIN)
    { }

    Rect(int x1, int y1, int x2, int y2)
        : bl(x1, y1), tr(x2, y2)
    { }

    Rect(const Point& bl_, const Point& tr_)
        : bl(bl_), tr(tr_)
    { }

    int Area() const {
        return (tr.x - bl.x) * (tr.y - bl.y);
    }

    std::vector<Point> Points() const {
        std::vector<Point> pts(4);
        pts[0] = bl;
        pts[1] = { bl.x, tr.y };
        pts[2] = tr;
        pts[3] = { tr.x, bl.y };
        return pts;
    }

    Rect& Union(const Rect& rect)
    {
        bl.x = std::min(bl.x, rect.bl.x);
        bl.y = std::min(bl.y, rect.bl.y);
        tr.x = std::max(tr.x, rect.tr.x);
        tr.y = std::max(tr.y, rect.tr.y);
        return *this;
    }
};

using Rects_t = std::vector<Rect>;
using PtSet_t = std::set<Point>;

bool PerfectRect(const Rects_t& rects)
{
    Rect perfect;
    int area = 0;
    PtSet_t ptset;
    for (const auto& rect : rects) {
        perfect.Union(rect);
        area += rect.Area();

        for (auto&& pt : rect.Points()) {
            if (ptset.count(pt)) {  // we only keep odd occurences for points
                ptset.erase(pt);
            } else {
                ptset.insert(pt);
            }
        }
    }
    // 面积不等，肯定不能构成完美矩形
    if (perfect.Area() != area) {
        return false;
    }
    // 最后剩下的顶点个数不是4，肯定不能构成完美矩形
    if (ptset.size() != 4) {
        return false;
    }
    // 最后剩下的顶点个数不是前面union后的矩形顶点，肯定不能构成完美矩形
    for (auto&& pt : perfect.Points()) {
        if (!ptset.count(pt)) {
            return false;
        }
    }
    return true;
}

int main()
{
    {
        Rects_t rects = {
            { 1,1,3,3 },
            { 3,1,4,2 },
            { 3,2,4,4 },
            { 1,3,2,4 },
            { 2,3,3,4 }
        };
        std::cout << std::boolalpha << PerfectRect(rects) << "\n";  // true
    }
    {
        Rects_t rects = {
            { 1,1,2,3 },
            { 1,3,2,4 },
            { 3,1,4,2 },
            { 3,2,4,4 }
        };
        std::cout << std::boolalpha << PerfectRect(rects) << "\n";  // false
    }
    {
        Rects_t rects = {
            { 1,1,3,3 },
            { 3,1,4,2 },
            { 1,3,2,4 },
            { 2,2,4,4 }
        };
        std::cout << std::boolalpha << PerfectRect(rects) << "\n";  // false
    }
    {
        Rects_t rects = {
            { 0, 0, 3, 1 },
            { 0, 0, 3, 1 },
            { 0, 3, 3, 3 }
        };
        std::cout << std::boolalpha << PerfectRect(rects) << "\n";  // false
    }
}
