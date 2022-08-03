#include "utils.h"

/*
给你一个整数数组 nums ，
请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），
并返回该子数组所对应的乘积。

示例 1:

输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:

输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
*/

// 这题的关键在于负数和负数相乘也可以达到最大值
// 仍然采用滑动窗口的策略，但是需要记录到目前位置的最大值和最小值
// 并不断更新它们，最大值和最小值有可能来自于当前元素自己，比如0
int MaxProductSubArray(const std::vector<int>& arr)
{
    int maxP = 1, minP = 1, res = INT_MIN;
    for (auto num : arr) {
        int a = num * maxP;
        int b = num * minP;
        maxP = std::max({num, a, b});
        minP = std::min({num, a, b});
        res = std::max(res, maxP);
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr = { 2, 3, -2, 4};
        std::cout << MaxProductSubArray(arr) << "\n";  // 6
    }
    {
        std::vector<int> arr = { -2, 0, -1};
        std::cout << MaxProductSubArray(arr) << "\n";  // 0
    }
}
