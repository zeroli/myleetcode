#include "utils.h"

/*
Given a sorted array, two integers k and x, find the k closest elements to x in the array.
The result should also be sorted in ascending order.
 If there is a tie, the smaller elements are always preferred.

Example 1:

Input:
 [1,2,3,4,5], k=4, x=3

Output:
 [1,2,3,4]

Example 2:

Input:
 [1,2,3,4,5], k=4, x=-1

Output:
 [1,2,3,4]

Note:

    The value k is positive and will always be smaller than the length of the sorted array.
    Length of the given array is positive and will not exceed 10^4
    Absolute value of elements in the array and x will not exceed 10^4
*/

// find the first one bigger than or equal to (>=) x, index returned
int LowerBound(const std::vector<int>& arr, int x)
{
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (x > arr[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

std::vector<int> KClosestElements(const std::vector<int>& arr, int k, int x)
{
    int n = arr.size();
    int index = LowerBound(arr, x);
    // index有可能为n，表示所有的数都比x要小
    // 向两边展开，两两比较，看谁离x近点，有点merge sort的感觉
    int left = index - 1, right = index;
    while (k-- > 0) {
        if (left < 0 || (right < n && (std::abs(arr[left] - x) > std::abs(arr[right] - x))))
        {
            right++;
        } else {
            left--;
        }
    }
    std::vector<int> ret;
    for (int i = left + 1; i < right; i++) {
        ret.push_back(arr[i]);
    }
    return ret;
}

int main()
{
    {
        std::vector<int> arr = { 1,2,3,4,5 };
        int k = 4, x = 3;
        std::cout << KClosestElements(arr, k, x) << "\n";  // 1,2,3,4
    }
    {
        std::vector<int> arr = { 1,2,3,4,5 };
        int k = 4, x = -1;
        std::cout << KClosestElements(arr, k, x) << "\n";  // 1,2,3,4
    }
    {
        std::vector<int> arr = { 1,2,3,4,5 };
        int k = 4, x = 6;
        std::cout << KClosestElements(arr, k, x) << "\n";  // 1,2,3,4,5
    }
}
