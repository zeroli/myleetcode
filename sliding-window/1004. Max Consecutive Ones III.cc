/*
1004. Max Consecutive Ones III

Given a binary array nums and an integer k,
 return the maximum number of consecutive 1's in the array if you can flip at most k 0's.



Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Example 2:

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.



Constraints:

    1 <= nums.length <= 105
    nums[i] is either 0 or 1.
    0 <= k <= nums.length


*/

#include "utils.h"

// 采用滑动窗口的方法
// 遍历数组，遍历到0的个数超过k了，考虑收缩窗口左边
// 没到k前，统计最大长度，因为其它都是1，
// 小于k个数的0可以flip成1
int Count(const std::vector<int>& arr, int k)
{
    int j = 0;
    int num0 = 0;
    int maxLen = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            num0++;
        }
        // 出现一个0，使得0的个数大于k了
        if (num0 > k) {
            // 窗口左边为1，收缩，直到遇到0
            while (arr[j] == 1) {
                j++;
            }
            num0--;  // 减少0的个数
            j++;  // 收缩窗口左边
        }
    #if 0  // 一个更好理解的窗口收缩代码
        // 统计窗口内的0的个数，超过不断收缩窗口左边
        // 直到窗口内的0的个数再次达到平衡
        while (num0 > k) {
            if (arr[j] == 0) {
                num0--;
            }
            j++;
        }
    #endif
        maxLen = std::max(maxLen, i - j + 1);
    }
    return maxLen;
}

int main()
{
    {
        std::vector<int> arr = { 1,1,1,0,0,0,1,1,1,1,0 };
        int k = 2;
        std::cout << Count(arr, k) << "\n";  // 6
    }
    {
        std::vector<int> arr = { 0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1 };
        int k = 3;
        std::cout << Count(arr, k) << "\n";  // 10
    }

}
