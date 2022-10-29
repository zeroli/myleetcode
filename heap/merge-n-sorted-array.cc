/*
给定n个排好序的数组，合并它们位一个最终排好序的数组
*/

#include "utils.h"

/*
合并n个排序数组，需要借助于最小堆，最小堆的大小为n
每次从最小堆里面弹出最小值，放入最后排序数组中，
然后从那个最小值对应的原数组中拿出下一个数放入最小堆中，
以此类推，最终遍历完所有的数组
*/

struct ElemAndArrayIdx
{
    int elem;
    int arrIdx;
    int nextIdx;

    friend bool operator >(const ElemAndArrayIdx& e1, const ElemAndArrayIdx& e2)
    {
        return e1.elem > e2.elem;
    }
};

std::vector<int> Merge(const std::vector<std::vector<int>>& narrs)
{
    int n = narrs.size();
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += narrs[i].size();
    }
    std::vector<int> arr;
    arr.reserve(total);
    // 最小堆，定义greater操作符
    std::priority_queue<ElemAndArrayIdx,
        std::vector<ElemAndArrayIdx>,
        std::greater<>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({narrs[i][0], i, 1});
    }

    while (!pq.empty()) {
        auto min = pq.top();
        pq.pop();

        arr.push_back(min.elem);
        if (min.nextIdx < narrs[min.arrIdx].size()) {
            pq.push({narrs[min.arrIdx][min.nextIdx], min.arrIdx, min.nextIdx+1});
        }
    }
    return arr;
}

int main()
{
    {
        std::vector<std::vector<int>> narrs = {
            { 1, 2, 3, 4, 5 },
            { 3,4, 8, 9, 10 },
            { 2, 3, 4, 5, 9 },
            { 0, 9, 10, 100, 1000}
        };
        std::cout << Merge(narrs) << "\n";
    }
}
