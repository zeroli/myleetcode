/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
// first sort the intervals according to their starting time, then merge the ones in sequence when the second one has smaller start value then the first one end value

static bool compare(Interval& a, Interval& b) {
    if (a.start < b.start) return true;
    return false;
}
    vector<Interval> merge(vector<Interval>& intervals) {
        if (intervals.size() <= 1) return intervals;
        sort(intervals.begin(), intervals.end(), compare);
        vector<Interval> r;
        
        Interval cur (intervals[0]);
        for (int ii = 1; ii < intervals.size(); ++ii) {
            if (cur.end >= intervals[ii].start) {
                cur.end = max(cur.end, intervals[ii].end); // merge 
            } else { // have a new interval
                r.push_back(cur);
                cur = intervals[ii];
            }
        }
        r.push_back(cur); // push the last one
        return r;
    }
};