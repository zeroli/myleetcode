/*
930. Binary Subarrays With Sum

Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

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

int NumOfSubarray(const std::vector<int>& arr, int sum)
{
    int res = 0;
    int cnt = 0;
    int beg = 0;
    int n = arr.size();
    for (int j = 0; j < n; j++) {
        sum -= arr[j];
        if (sum == 0) {
            cnt = 0;
        }
        if (beg > j) beg = j;
        while (beg < n && sum == 0) {
            cnt++;
            sum += arr[beg];
            beg++;
        }

        res += cnt;
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
        std::vector<int> arr = { 0,0,0,0,0 };
        int k = 0;
        std::cout << NumOfSubarray(arr, k) << "\n";  // 0
    }

}
