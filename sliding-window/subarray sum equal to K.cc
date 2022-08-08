#include "utils.h"

// 找到所有的子数组，它们的和都等于一个给定的数K
// 数组元素都是正数

// 本题思路是采用sliding window的想法
std::vector<std::pair<int,int>> FindSubarraySumK(const std::vector<int>& arr, int K)
{
    std::vector<std::pair<int,int>> pairs;
    int start = 0;
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        // 一旦累加和超过K，就需要收缩左边窗口
        // 使窗口内的累加和重新达到K，或小于K
        while (sum > K) {
            sum -= arr[start];
            start++;
        }
        if (sum == K) {
            pairs.push_back({start, i});
        }
    }
    return pairs;
}

int main()
{
    std::vector<int> arr = { 2, 3, 6, 4, 9, 0, 11 };
    std::cout << FindSubarraySumK(arr, 9) << "\n";  // (1,2), (4,4), (4,5)
}
