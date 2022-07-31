/*
Find the Minimum length Unsorted Subarray,
 sorting which makes the complete array sorted

Given an unsorted array arr[0..n-1] of size n,
find the minimum length subarray arr[s..e] such that
 sorting this subarray makes the whole array sorted.
Examples:

    If the input array is [10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60],
     your program should be able to find that the subarray lies between the indexes 3 and 8.
    If the input array is [0, 1, 15, 25, 6, 7, 30, 40, 50],
     your program should be able to find that the subarray lies between the indexes 2 and 5.
*/

/*
这个题目提供的数组可以分为这样的三个部分：
1. 递增， 2. 不有序，3. 递增
现在要求找出可以使整个数组有序的最小的部分2
0, 1, 15, 25, 6, 7, 30, 40, 50
部分1: 0, 1
部分2：15, 25, 6, 7
部分3: 30, 40, 50
*/

#include "utils.h"

int LowerBound(const std::vector<int>& arr, int left, int right, int target)
{
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (target > arr[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

std::vector<int> Unsorted(const std::vector<int>& arr)
{
    int n = arr.size();
    // 从前往后遍历，找到第一个元素，使得它比它的下一个值要大，定为i
    int i = 0;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            break;
        }
    }
    if (i == n - 1) {  // 数组已经有序
        return {};
    }
    // 从后往前遍历，找到第一个元素，使得它比它的前一个值要小，定位j
    int j = n - 1;
    for (j = n - 1; j > 0; j--) {
        if (arr[j] < arr[j - 1]) {
            break;
        }
    }
    assert(i < j);

    // 找到区间[i, j]之前最小和最大值
    int min = INT_MAX, max = INT_MIN;
    for (int k = i; k <= j; k++) {
        min = std::min(arr[k], min);
        max = std::max(arr[k], max);
    }

    // 找到最小值对应前一部分有序区间的lower-bound
    // 有多少元素比它小
    int ib1 = LowerBound(arr, 0, i, min);
    // 找到最大值对应后一部分有序区间的lower-bound
    // 有多少元素比它小
    int ib2 = LowerBound(arr, j+1, n, max);
    // 即使ib2是下一个index: [ib1, ib2)，但是下面仍然用ib2来索引end iterator
    return std::vector<int>(&arr[ib1], &arr[ib2]);
}

int main()
{
    {
        std::vector<int> arr = { 10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60 };
        std::cout << Unsorted(arr) << "\n";  // (3, 8): [30, 25, 40, 32, 31, 35]
    }
    {
        std::vector<int> arr = { 0, 1, 15, 25, 6, 7, 30, 40, 50 };
        std::cout << Unsorted(arr) << "\n";  // (2,5) : [15, 25, 6, 7]
    }
}
