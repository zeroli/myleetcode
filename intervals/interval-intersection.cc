#include "utils.h"
#include "internal-util.h"

bool GetOverlap(const Interval& a, const Interval& b, Interval& overlap)
{
    overlap = { std::max(a.start, b.start), std::min(a.end, b.end) };
    if (overlap.start > overlap.end) {
        return false;
    } else {
        return true;
    }
}
IntervalList_t Intersect2Intervals(IntervalList_t& intervals_1, IntervalList_t& intervals_2)
{
    IntervalList_t intersectIntervals;
    // merge sort idea
    Interval overlap;
    int i = 0, j = 0;
    while (i < intervals_1.size() && j < intervals_2.size()) {
#if 1
        if (GetOverlap(intervals_1[i], intervals_2[j], overlap)) {
            intersectIntervals.push_back(overlap);
        }
        // who ends first, go to its next
        if (intervals_1[i].end < intervals_2[j].end) {
            i++;
        } else {
            j++;
        }
#else
        if (GetOverlap(intervals_1[i], intervals_2[j], overlap)) {
            intersectIntervals.push_back(overlap);
            if (overlap.end == intervals_1[i].end && overlap.end == intervals_2[j].end) {
                i++;
                j++;
            } else if (overlap.end == intervals_1[i].end) {
                i++;
                intervals_2[j].start = overlap.end;  // chunk interval 2
            } else {
                j++;
                intervals_1[i].start = overlap.end;  // chunk interval 1
            }
        } else if (intervals_1[i].start < intervals_2[j].start) {
            i++;
        } else {
            j++;
        }
#endif
    }
    return intersectIntervals;
}

int main()
{
    {
        IntervalList_t intervals_1 = {
            { 1, 3 },
            { 5, 6 },
            { 7, 9 }
        };
        IntervalList_t intervals_2 = {
            { 2, 3 },
            { 5, 7 }
        };
        std::cout << "intersection of 2 lists of intervals:\n" <<
            Intersect2Intervals(intervals_1, intervals_2) << "\n";
    }
    {
        IntervalList_t intervals_1 = {
            { 1, 3 },
            { 5, 7 },
            { 9, 12 }
        };
        IntervalList_t intervals_2 = {
            { 5, 10 }
        };
        std::cout << "intersection of 2 lists of intervals:\n" <<
            Intersect2Intervals(intervals_1, intervals_2) << "\n";
    }
}
