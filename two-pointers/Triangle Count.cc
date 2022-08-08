#include "utils.h"

/*
Given an array of integers, how many three numbers can be found in the array,
 so that we can build an triangle whose three edges length is the three numbers that we find?

Given array S = [3,4,6,7], return 3. They are:

[3,4,6]
[3,6,7]
[4,6,7]

Given array S = [4,4,4,4], return 4. They are:
[4(1),4(2),4(3)]
[4(1),4(2),4(4)]
[4(1),4(3),4(4)]
[4(2),4(3),4(4)]
*/

int Count(std::vector<int>& arr)
{
    // 满足三角形的边长要求其中2个数之和大于另外1个数
    std::sort(arr.begin(), arr.end());

    int cnt = 0;
    for (int i = 0; i < arr.size(); i++) {
        int left = 0, right = i - 1;
        while (left < right) {
            // 与two-sum II 解法很类似
            if (arr[left] + arr[right] > arr[i]) {
                cnt += right - left;
                right--;
            } else {
                left++;
            }
        }
    }
    return cnt;
}

int main()
{
    {
        std::vector<int> arr = { 3, 4, 6, 7 };
        std::cout << Count(arr) << "\n";  // 3
    }
    {
        std::vector<int> arr = { 4,4,4,4 };
        std::cout << Count(arr) << "\n";  // 4
    }
}
