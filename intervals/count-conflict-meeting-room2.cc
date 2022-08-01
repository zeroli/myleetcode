#include "utils.h"
#include "internal-util.h"

#include <queue>

using Meeting_t = Interval;
using Meetings_t = IntervalList_t;

struct MeetingEndComp {
    bool operator ()(const Meeting_t& m1, const Meeting_t& m2) const
    {
        return m1.end > m2.end;
    }
};

int CountMeetingRooms(Meetings_t& meetings)
{
    int maxcnt = 0;

    std::sort(meetings.begin(), meetings.end());
    // build one min-heap with end time
    std::priority_queue<Meeting_t, Meetings_t, MeetingEndComp> pq;
    for (auto&& meeting : meetings) {
        // check each start time, and remove those meetings ended
        // how to find those meetings quickly (started before this one, but have ended)?
        // use min-heap with end time, so that end time is sorted for those meetings
        // surely, we could build one sorted meetings with end time,
        // and binary search with this startime for how many meetings with end time
        // are before this start time (find lower-bound)
        while (!pq.empty() && pq.top().end <= meeting.start) {
            pq.pop();
        }
        pq.push(meeting);
        maxcnt = std::max((int)pq.size(), maxcnt);
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
