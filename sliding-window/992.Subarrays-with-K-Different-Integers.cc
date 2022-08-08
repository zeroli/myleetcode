/*
Given an integer array nums and an integer k, return the number of good subarrays of nums.

A good array is an array where the number of different integers in that array is exactly k.

    For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.

A subarray is a contiguous part of an array.



Example 1:

Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:

Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].



Constraints:

    1 <= nums.length <= 2 * 104
    1 <= nums[i], k <= nums.length
*/

#include "utils.h"

int NumOfSubarr(const std::vector<int>& arr, int k)
{
    // [j, i]  => [j + prefix, i] (has unique k, cannot shrink any more)
    // shrink prefix times, so that res += prefix + 1
    std::map<int, int> freqs;
    int start = 0;
    int n = arr.size();
    int res = 0;
    int prefix = 0;
    for (int i = 0; i < n; i++) {
        freqs[arr[i]]++;

        // 窗口不平衡了，有>K个不同的数字
        // 可以肯定当前数字是一个unique数字
        if (freqs.size() > k) {
            // 开始不断收缩窗口左边那些对当前窗口状态不影响的数字
            // 当前窗口状态是>K个不同的数字
            // 那些对窗口状态不影响的数字就是它们出现的频率很多
            while (start < i && (freqs[arr[start]] > 1)) {
                --freqs[arr[start]];
                start++;
            }
            // 直到发现一个数字，后面不再存在跟它重复
            // 去除它，重新让窗口平衡
            if (--freqs[arr[start]] == 0) {
                freqs.erase(arr[start]);
            }
            start++;
            // 开始进行prefix统计
            prefix = 0;
        }
        // 窗口平衡了，做最后的统计
        if (freqs.size() == k) {
            // 在窗口平衡的前提下，可以统计有多少数字可以去除
            // 不会影响窗口平衡
            while (start < i && (freqs[arr[start]] > 1)) {
                --freqs[arr[start]];
                start++;
                // 注意这个prefix会一直保持在那里直到下次窗口不平衡
                // 因为紧接着下次迭代，如果窗口仍然平衡，这次去除的数字
                // 也不会影响下次窗口的平衡
                prefix++;
            }
            res += 1 + prefix;
        }
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr = { 1,2,1,2,1 };
        int k = 2;
        std::cout << NumOfSubarr(arr, k) << "\n";  // 10
        // (1,2),
    }
    {
        std::vector<int> arr = { 1,2,1,2,3 };
        int k = 2;
        std::cout << NumOfSubarr(arr, k) << "\n";  // 7
        // (1,2),
    }
    {
        std::vector<int> arr = { 1,2,1,3,4 };
        int k = 3;
        std::cout << NumOfSubarr(arr, k) << "\n";  // 3
        // (1,2,1,3), (2,1,3), (1,3,4), 1 + 1 + 1
    }

}

/*
Intuition

If the subarray [j, i] contains K unique numbers, and first prefix numbers also appear in [j + prefix, i] subarray, we have total 1 + prefix good subarrays. For example, there are 3 unique numers in [1, 2, 1, 2, 3]. First two numbers also appear in the remaining subarray [1, 2, 3], so we have 1 + 2 good subarrays: [1, 2, 1, 2, 3], [2, 1, 2, 3] and [1, 2, 3].

Linear Solution

We can iterate through the array and use two pointers for our sliding window ([j, i]). The back of the window is always the current position in the array (i). The front of the window (j) is moved so that A[j] appear only once in the sliding window. In other words, we are trying to shrink our sliding window while maintaining the same number of unique elements.

To do that, we keep tabs on how many times each number appears in our window (m). After we add next number to the back of our window, we try to remove as many as possible numbers from the front, until the number in the front appears only once. While removing numbers, we are increasing prefix.

If we collected K unique numbers, then we found 1 + prefix sequences, as each removed number would also form a sequence.
*/
