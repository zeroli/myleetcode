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
    for (int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i-1];
    }
    std::vector<int> sorted(arr.size(), 0);
    // loop forward will have not kept relative order for same value
    for (auto num : arr) {
        sorted[--counts[num]] = num;
    }
    return sorted;
}

int main()
{
    {
        std::vector<int> arr = { 0, 2, 3, 5, 1, 1, 7, 7, 6 };
        std::cout << CountSort(arr) << "\n";
    }
}
