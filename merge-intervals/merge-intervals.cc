#include "utils.h"

#include "internal-util.h"

std::vector<Interval> MergeIntervals(std::vector<Interval>& intervals)
{
    std::sort(intervals.begin(), intervals.end());

    std::vector<Interval> merged;
    int start = 0, end = 0;
    start = intervals[0].start;
    end = intervals[0].end;

    for (int i = 1; i < intervals.size(); i++) {
        auto&& cur = intervals[i];
        if (cur.start <= end) {  // overlapped
            end = std::max(cur.end, end);
        } else {
            merged.push_back({start, end});
            start = cur.start;
            end = cur.end;
        }
    }
    merged.push_back({start, end});
    return merged;
}

int main()
{
    {
        std::vector<Interval> intervals = {
            { 1, 4 },
            { 2, 5 },
            { 7, 9 }
        };
        auto merged = MergeIntervals(intervals);
        std::cout << "merged intervals: \n" << merged << "\n";
    }
    {
        std::vector<Interval> intervals = {
            { 6, 7 },
            { 2, 4 },
            { 5, 9 }
        };
        auto merged = MergeIntervals(intervals);
        std::cout << "merged intervals: \n" << merged << "\n";
    }
    {
        std::vector<Interval> intervals = {
            { 1, 4 },
            { 2, 6 },
            { 3, 5 }
        };
        auto merged = MergeIntervals(intervals);
        std::cout << "merged intervals: \n" << merged << "\n";
    }
}
