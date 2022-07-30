#include "utils.h"

/*
Given an array of integers,
 find how many pairs in the array such that their sum is bigger than a specific target number.
  Please return the number of pairs.

Given numbers = [2, 7, 11, 15], target = 24. Return 1. (11 + 15 is the only pair)
Do it in O(1) extra space and O(nlogn) time.
*/

int TwoSumBiggrThan(std::vector<int>& arr, int target)
{
    int n = arr.size();
    std::sort(arr.begin(), arr.end());

    int cnt = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        if (arr[left] + arr[right] > target) {
            // 所以以right为结尾的，从left 开始到right-1都可以与right进行组合
            // 因为left => right，一直增大
            cnt += right - left;  // 注意这里不是right - left + 1，因为要去掉right跟自己组合
            right--;  // 接着查看是否有组合也是满足的，以right-1为结尾的组合
        } else {
            left++;
        }
    }
    return cnt;
}

int main()
{
    std::vector<int> arr = { 2, 7 , 11, 15 };
    std::cout << TwoSumBiggrThan(arr, 24) << "\n";  // 1
}
