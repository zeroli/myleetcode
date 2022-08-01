#include "utils.h"

/*
Given an array nums with n objects colored red, white, or blue,
 sort them in-place so that objects of the same color are adjacent,
  with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]
*/

std::vector<int> ColorSort(std::vector<int>& arr)
{
    enum { RED = 0, WHITE, BLUE };
    int ir = 0, ib = arr.size();
    int iw = 0;
    // [0, ir)：RED
    // [ir, iw): GREEN
    // iw: 当前检查的元素
    // [ib, n): BLUE
    while (iw < ib) {
        if (arr[iw] == RED) {
            std::swap(arr[iw], arr[ir]);
            ir++;
            iw++;
            // 这里需要iw++，因为我们知道交换回来的arr[iw]是GREEN
        } else if (arr[iw] == BLUE) {
            --ib;
            std::swap(arr[iw], arr[ib]);
            // 这里不要iw++，因为交换回来的arr[iw]有可能是RED
            // 下一轮还需要再次判断是否为RED还是GREEN
        } else {
            iw++;
        }
    }
    return arr;
}

int main()
{
    {
        std::vector<int> arr = { 2,0,2,0,1,0 };
        std::cout << ColorSort(arr) << "\n";  // 0,0,0,1,2,2
    }
    {
        std::vector<int> arr = { 2,0,2,1,1,0 };
        std::cout << ColorSort(arr) << "\n";  // 0,0,1,1,2,2
    }
    {
        std::vector<int> arr = { 2,0,1 };
        std::cout << ColorSort(arr) << "\n";  // 0, 1, 2
    }
}
