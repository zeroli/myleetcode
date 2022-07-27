#include "utils.h"
#include "internal-util.h"

using Meeting_t = Interval;
using Meetings_t = IntervalList_t;

struct TimePoint {
    int time;  // start or end of meeting
    bool isStart;  // 1: start meeting, 0: end meeting

    friend bool operator <(const TimePoint& tp1, const TimePoint& tp2)
    {
        if (tp1.time != tp2.time) {
            return tp1.time < tp2.time;
        }
        // end time is smaller than start time
        return tp1.isStart < tp2.isStart;
    }
};

int CountMeetingRooms(const Meetings_t& meetings)
{
    int cnt = 0;
    int maxcnt = 0;
    std::vector<TimePoint> tps;
    for (auto&& meeting : meetings) {
        tps.push_back({meeting.start, true});
        tps.push_back({meeting.end, false});
    }
    std::sort(tps.begin(), tps.end());
    for (auto&& tp : tps) {
        if (tp.isStart) {
            cnt++;
        } else {
            cnt--;
        }
        std::cout << "time: " << tp.time << ", cnt: " << cnt << "\n";
        maxcnt = std::max(cnt, maxcnt);
    }
    return maxcnt;
}

int main()
{
    {
        Meetings_t meetings = {
            { 4, 5 },
            { 2, 3 },
            { 2, 4 },
            { 3, 5 }
        };
        std::cout << "need meeting rooms: " << CountMeetingRooms(meetings) << "\n";
    }
    {
        Meetings_t meetings = {
            { 1, 4 },
            { 2, 5 },
            { 7, 9 }
        };
        std::cout << "need meeting rooms: " << CountMeetingRooms(meetings) << "\n";
    }
    {
        Meetings_t meetings = {
            { 6, 7 },
            { 2, 4 },
            { 8, 12 }
        };
        std::cout << "need meeting rooms: " << CountMeetingRooms(meetings) << "\n";
    }
}
