#include "utils.h"
#include "internal-util.h"

#include <queue>

struct Task {
    int start;
    int end;
    int cpu;

    friend bool operator <(const Task& task1, const Task& task2)
    {
        if (task1.start != task2.start) {
            return task1.start < task2.start;
        }
        return task1.end < task2.end;
    }
};
using TaskList_t = std::vector<Task>;

struct TimePoint {
    int time;  // start or end of task
    bool isStart;  // 1: start task, 0: end task
    int cpu;    // cpu load

    friend bool operator <(const TimePoint& tp1, const TimePoint& tp2)
    {
        if (tp1.time != tp2.time) {
            return tp1.time < tp2.time;
        }
        // end time is smaller than start time
        return tp1.isStart < tp2.isStart;
    }
};

int MaxCpuLoad(const TaskList_t& tasks)
{
    int maxCpu = 0;
    std::vector<TimePoint> tps;
    for (auto&& task : tasks) {
        tps.push_back({task.start, true, task.cpu});
        tps.push_back({task.end, false, task.cpu});
    }
    std::sort(tps.begin(), tps.end());

    int cpu = 0;
    for (auto&& tp : tps) {
        if (tp.isStart) {
            cpu += tp.cpu;
        } else {
            cpu -= tp.cpu;
        }
        maxCpu = std::max(maxCpu, cpu);
    }
    return maxCpu;
}

int main()
{
    {
        TaskList_t tasks = {
            { 1, 4, 3 },
            { 2, 5, 4 },
            { 7, 9, 6 }
        };
        std::cout << "max cpu load: " << MaxCpuLoad(tasks) << "\n";
    }

    {
        TaskList_t tasks = {
            { 6,7,10 },
            { 2,4,11 },
            { 8,12,15 }
        };
        std::cout << "max cpu load: " << MaxCpuLoad(tasks) << "\n";
    }

    {
        TaskList_t tasks = {
            { 1,4,2 },
            { 2,4,1 },
            { 3,6,5 }
        };
        std::cout << "max cpu load: " << MaxCpuLoad(tasks) << "\n";
    }
}
