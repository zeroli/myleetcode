/*
930. Binary Subarrays With Sum

Given a binary array nums and an integer goal,
return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.

Example 1:

Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Example 2:

Input: nums = [0,0,0,0,0], goal = 0
Output: 15

Constraints:

    1 <= nums.length <= 3 * 104
    nums[i] is either 0 or 1.
    0 <= goal <= nums.length
*/

#include "utils.h"

// 这个题目与992.Subarrays-with-K-Different-Integers 解法类似
// 采用滑动窗口来解答
int NumOfSubarray(const std::vector<int>& arr, int sum)
{
    int res = 0;
    int prefix = 0;
    int start = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        sum -= arr[i];
        // 当遇到一个数字使得sum<0时，可以肯定这个数字是1
        // 窗口内的数组和不再满足sum了（前一次迭代满足）
        // 不满足，收缩窗口左边，开始统计prefix
        // prefix的意思是指有多少可以收缩，从而使得后面一些数字累加和为sum
        if (sum < 0) {
            // 如何这个start收缩，不能使得窗口重新平衡也没关系
            // 现在的pattern应该类似于这样的
            // 前面很多0，然后是一个1开头，最后是一个1（当前位置）
            // 0000010000xxxxxx1
            // 收缩左边0（不会改变窗口当前状态，不会让窗口平衡）
            // 直到找到第一个1（打破窗口当前状态）
            while (start < i && arr[start] == 0) {
                start++;
            }
            // 找到1了，再收缩，窗口平衡
            sum += arr[start];
            start++;
            // 开始进行prefix统计
            prefix = 0;
        }
        // 窗口平衡前提下，统计可以收缩多少同时维持窗口平衡
        if (sum == 0) {
            while (start < i && arr[start] == 0) {
                start++;
                prefix++;
            }
            res += prefix + 1;
        }
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr = { 1,0,1,0,1 };
        int k = 2;
        std::cout << NumOfSubarray(arr, k) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 0,1,0,1,1 };
        int k = 2;
        std::cout << NumOfSubarray(arr, k) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 0,0,0,0,0 };
        int k = 0;
        std::cout << NumOfSubarray(arr, k) << "\n";  // 15
    }

}
