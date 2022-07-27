#ifndef MERGE_INTERVAL_UTIL_H_
#define MERGE_INTERVAL_UTIL_H_

#include <vector>

struct Interval {
    int start;
    int end;

    friend bool operator ==(const Interval& a, const Interval& b)
    {
        return a.start == b.start && a.end == b.end;
    }
    friend bool operator !=(const Interval& a, const Interval& b)
    {
        return !(a == b);
    }

    friend bool operator <(const Interval& a, const Interval& b)
    {
        if (a.start != b.start) {
            return a.start < b.start;
        }
        return a.end < b.end;
    }

    friend bool operator >(const Interval& a, const Interval& b)
    {
        return b < a;
    }

    friend std::ostream& operator <<(std::ostream& outstr, const Interval& interval)
    {
        return outstr << "(" << interval.start << "," << interval.end << ")";
    }
};

using IntervalList_t = std::vector<Interval>;

#endif  // MERGE_INTERVAL_UTIL_H_
