#include "utils.h"
#include "internal-util.h"

struct EmployeeInterval {
    Interval interval;
    int employee_id;
    int index_of_internvals;

    friend std::ostream& operator <<(std::ostream& outstr, const EmployeeInterval& e)
    {
        return outstr << e.employee_id
            << ": " << e.interval << "[" << e.index_of_internvals << "]";
    }
};

struct EmployeeIntervalCmp {
    bool operator ()(const EmployeeInterval& e1, const EmployeeInterval& e2) const
    {  // we'd like to build min-heap, so use > here
        return e1.interval > e2.interval;
    }
};

IntervalList_t FreeIntervals(const std::vector<IntervalList_t>& intervals)
{
    std::priority_queue<EmployeeInterval, std::vector<EmployeeInterval>, EmployeeIntervalCmp> pq;
    for (int ie = 0; ie < intervals.size(); ie++) {
        pq.push({ intervals[ie][0], ie, 0 });
    }

    EmployeeInterval prev = pq.top();

    IntervalList_t list;
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        // std::cout << "prev: " << prev << "\n";
        // std::cout << "cur: " << cur << "\n";
        if (cur.interval.start > prev.interval.end) {  // has free interval
            list.push_back({ prev.interval.end, cur.interval.start });
            prev = cur;
        } else {  // overlap
            if (cur.interval.end > prev.interval.end) {
                prev = cur;
            }
        }
        // add more intervals for this employee
        auto&& employee_intervals = intervals[cur.employee_id];
        if (cur.index_of_internvals + 1 < employee_intervals.size()) {
            pq.push({ employee_intervals[cur.index_of_internvals + 1], cur.employee_id, cur.index_of_internvals + 1});
        }
    }
    return list;
}

int main()
{
    {
        std::vector<IntervalList_t> intervals = {
            { { 1, 3 }, { 5, 6 } },
            { { 2, 3 }, { 6, 8 } }
        };
        std::cout << "free intervals: \n" << FreeIntervals(intervals) << "\n";
    }
    {
        std::vector<IntervalList_t> intervals = {
            { { 1, 3 }, { 9, 12 } },
            { { 2, 4 } },
            { { 6, 8 } }
        };
        std::cout << "free intervals: \n" << FreeIntervals(intervals) << "\n";
    }
    {
        std::vector<IntervalList_t> intervals = {
            { { 1, 3 } },
            { { 2, 4 } },
            { { 3, 5 }, { 7, 9 } }
        };
        std::cout << "free intervals: \n" << FreeIntervals(intervals) << "\n";
    }
}
