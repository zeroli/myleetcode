#include "utils.h"

/*
给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，
并返回该子数组的长度。

示例 1:

输入: nums = [0,1]
输出: 2
说明: [0, 1] 是具有相同数量0和1的最长连续子数组。

示例 2:

输入: nums = [0,1,0]
输出: 2
说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。

提示：

1 <= nums.length <= 105
nums[i] 不是 0 就是 1
*/

int LongestSubarray(std::vector<int>& arr)
{
    // 将1变成-1，将0变成1
    for (auto& num : arr) {
        if (num == 1) num = -1;
        if (num == 0) num = 1;
    }
    // 相同数量的1/0子数组在变成1/-1之后，累加和就是0
    // 利用前缀和，如果有一段区间的累加和为0，那么那一段就是相同数量的1/0子数组
    // 利用map来记录累加和对应index
    std::map<int, int> map;
    // ****添加哨兵，累加和为0时，对应的位置为-1
    // 这是行非常关键的代码
    // 1, -1 => 1, 0 （前缀和）
    map[0] = -1;
    int sum = 0;
    int maxLen = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        // 前面出现了相同的前缀和，说明那个位置到这个位置i之间的累加和就是0
        if (map.count(sum) > 0) {
            // 这里是i-j，不是i-j+1，因为j到i之间的元素累加和为0，不包括i
            maxLen = std::max(maxLen, (i - map[sum]));
            // NOTE：不更新map[sum]，因为之前的位置i更小，更有可能获取更长的len
        } else {
            map[sum] = i;
        }
    }
    return maxLen;
}

int main()
{
    {
        std::vector<int> arr = { 0, 1 };
        std::cout << LongestSubarray(arr) << "\n";  // 2
    }
    {
        std::vector<int> arr = { 0, 1, 0 };
        std::cout << LongestSubarray(arr) << "\n";  // 2
    }
}
