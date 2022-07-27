/*
Find minimum element in sorted and rotated array

You have a sorted and rotated array arr[] of size n
 where elements are sorted and rotated circularly.
 Write a program to find the minimum element in the array.

*/

#include "utils.h"

int MinAtIndexNoDup(const std::vector<int>& arr)
{
    int left = 0, right = arr.size() - 1;
    while (left < right) { // NOTE this !!! "<"
        if (arr[left] < arr[right]) {
            break;
        }
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
        std::cout << MinAtIndexWithDup(arr) << "\n";
    }
    {
        std::vector<int> arr = { 1, 1, 2, 0, 1, 1, 1, 1, 1 };
        std::cout << MinAtIndexWithDup(arr) << "\n";
    }
}
