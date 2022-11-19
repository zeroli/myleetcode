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
// loop one by one, push the ones before, and merge and then push the ones after, 
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> r;
        if (intervals.empty() || intervals.back().end < newInterval.start) {
            r = intervals;
            r.push_back(newInterval);
            return r;
        }
        if (intervals[0].start > newInterval.end) {
            r.push_back(newInterval);
            r.insert(r.begin()+1, intervals.begin(), intervals.end());
            return r;
        }
        
        size_t ii = 0;
        int olstart = newInterval.start;
        int olend = newInterval.end;
        bool inserted = false;
        while (ii < intervals.size()) {
            if (intervals[ii].end < newInterval.start) { // the ones before
                r.push_back(intervals[ii]);
            }
            else {
                if (intervals[ii].start > newInterval.end) { // the ones after
                    if (!inserted) r.push_back(Interval(olstart, olend)); // insert the new one
                    inserted = true;
                    r.push_back(intervals[ii]);
                }
                else {//overlap: ii.end >= start, ii.start <= end // merge
                    olstart = min(olstart, intervals[ii].start);
                    olend = max(olend, intervals[ii].end);
                }
            }
            ++ii;
        }
        if (!inserted) r.push_back(Interval(olstart, olend)); // insert the new one in case no one after
        return r;   
    }
};