/*
Find minimum element in sorted and rotated array

You have a sorted and rotated array arr[] of size n
 where elements are sorted and rotated circularly.
 Write a program to find the minimum element in the array.

*/

#include "utils.h"

// 此题可以假设元素就是[0,1]，并没有rotated
// left = 0, right = 1，一些细节的地方就可以很好的处理
int MinAtIndexNoDup(const std::vector<int>& arr)
{
    int left = 0, right = arr.size() - 1;
    // right 初始化为n-1, 是因为下面要用right对应的数组元素跟mid数组元素进行比较。
    // 采用left < right, 而不是left <= right，是因为下面代码中要right有可能不会变化，
    // 这样则需要left < right，否则会有可能死循环，因为一旦left=right时，再次进入
    // 循环，mid=left，right=mid (因为arr[mid]=arr[right])，left仍然等于right
    // 所以这里不能用<=进行判断
    // 类似的，如果while循环里面有right不发生变化，condition一定是用<，而不是<=
    // 同时，循环代码中，不能有left = mid出现，因为一旦mid=left(只有2个元素left+1=right),
    // left/right就不会发生变化，代码将进入死循环。
    while (left < right) { // NOTE this !!! "<"
        int mid = left + (right - left) / 2;

        #if 1
        if (arr[mid] > arr[right]) {  // left part is ascending order
            left = mid + 1;
        } else {
            right = mid;
        }
        #else
        // left might be same as mid
        if (arr[left] <= arr[mid]) {  // left part is ascending order
            left = mid + 1;  // go to right part for min
        } else {
            right = mid;  // go to left part for min, including this mid
        }
        #endif
    }
    return arr[left];
}

int MinAtIndexWithDup(const std::vector<int>& arr)
{
    int left = 0, right = arr.size() - 1;
    while (left < right) {  // NOTE, "<"
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[right]) {  // left part ascending order
            left = mid + 1;  // go to right part for min
        } else if (arr[mid] == arr[right]) {
            // decrement right is safe, since we have mid to guard, if right/mid is smallest
            // case 1: left = mid = right, mid sits on left, then min is on right of it
            // case 2: left = mid = right, mid sits on right, then min is on left of it
            right--;  // 2 cases: mid is on left or right, both
        } else {  // <, mid is on the right part
            right = mid;
        }
    }
    return arr[left];
}

int main()
{
    {
        std::vector<int> arr = { 0, 1 };
        std::cout << MinAtIndexNoDup(arr) << "\n";  // 0
    }
    {
        std::vector<int> arr = { 4, 5, 6, 7, 1, 2, 3 };
        std::cout << MinAtIndexNoDup(arr) << "\n";  // 1
    }
    {
        std::vector<int> arr = { 8, 9, 4, 5, 6, 7 };
        std::cout << MinAtIndexNoDup(arr) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 3, 4, 5, 6, 7 };
        std::cout << MinAtIndexNoDup(arr) << "\n";  // 3
    }
    {
        std::vector<int> arr = { 3, 2 };
        std::cout << MinAtIndexNoDup(arr) << "\n";  // 2
    }
    {
        std::vector<int> arr = { 1, 1, 1, 1, 1, 1 };
        std::cout << MinAtIndexWithDup(arr) << "\n";  // 1
    }
    {
        std::vector<int> arr = { 1, 1, 2, 0, 1, 1, 1, 1, 1 };
        std::cout << MinAtIndexWithDup(arr) << "\n";  // 0
    }
}
