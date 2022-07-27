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

int Count(const std::vector<int>& arr, int k)
{
    int j = 0;
    int num0 = 0;
    int maxLen = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            num0++;
        }
        if (num0 > k) {
            while (arr[j] == 1) {
                j++;
            }
            num0--;
            j++;
        }

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
