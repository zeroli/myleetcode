#include "utils.h"

int FindMax(const std::vector<int>& arr)
{
    int max = INT_MIN;
    for (auto num : arr) {
        max = std::max(max, num);
    }
    return max;
}

std::vector<int> CountSort(const std::vector<int>& arr)
{
    int N = FindMax(arr);
    std::vector<int> counts(N+1, 0);
    for (auto num : arr) {
        counts[num]++;
    }
    // inclusive_scan的方法计算prefix sum
    for (int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i-1];
    }
    std::vector<int> sorted(arr.size(), 0);
    // loop forward will have not kept relative order for same value
    for (auto num : arr) {
        sorted[--counts[num]] = num;
    }
    // 1) 相同值如果需要保持相对顺序，则可以从后往前遍历
    return sorted;
}

// 2) 对于相同值，保持相对顺序，采用exclusive_scan的计算prefix sum
std::vector<int> CountSort1(const std::vector<int>& arr)
{
    int N = FindMax(arr);
    std::vector<int> counts(N+2, 0);  // 为第一个0腾出一个位置
    for (auto num : arr) {
        counts[num+1]++;  // 注意这里时num+1，将计数统计到下一个位置
    }
    std::cout << "counts1: " << counts << "\n";
    for (int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i-1];
    }
    std::cout << "counts2: " << counts << "\n";
    std::vector<int> sorted(arr.size(), 0);
    for (auto num : arr) {
        sorted[counts[num]++] = num;  // 从前往后填充相同元素
    }
    return sorted;
}

int main()
{
    {
        std::vector<int> arr = { 0, 2, 3, 5, 1, 1, 7, 7, 6 };
        std::cout << CountSort(arr) << "\n";
    }
    {
        std::vector<int> arr = { 0, 1, 2, 2, 3, 4, 5 };
        std::cout << CountSort(arr) << "\n";
    }
}
