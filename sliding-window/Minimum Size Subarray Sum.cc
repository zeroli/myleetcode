#include "utils.h"

/*
Given an array of n positive integers and a positive integers,
 find the minimal length of a contiguous subarray of which the sum ≥s.
  If there isn't one, return 0 instead.

Input:
s = 7, nums = [2,3,1,2,4,3]
Output:
 2

Explanation:
the subarray
[4,3]
 has the minimal length under the problem constraint.
*/

// 这题目与sliding-window\subarray sum equal to K.cc，思路一样
int MinSizeSubarr(const std::vector<int>& arr, int target)
{
    int n = arr.size();
    int minSize = n + 1;
    int start = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        while (sum >= target) {
            minSize = std::min(minSize, i - start + 1);
            // 收缩窗口左边
            sum -= arr[start];
            start++;
        }
    }
    return (minSize == (n + 1)) ? 0 : minSize;
}

int main()
{
    {
        std::vector<int> arr = { 2,3,1,2,4,3 };
        std::cout << MinSizeSubarr(arr, 7) << "\n";  // 2
    }
    {
        std::vector<int> arr = { 2,3,1,2,4,3 };
        std::cout << MinSizeSubarr(arr, 20) << "\n";  // 0
    }
}
