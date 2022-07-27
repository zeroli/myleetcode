#include "utils.h"

// return lower-bound (the first >= target) of target in array
// return -1 if cannot find it
int lowerBound(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (target > arr[mid]) {
            left = mid + 1;
        } else {  // target <= arr[mid]
            right = mid;  // arr[mid] might be the lower-bound (>=)
        }
    }
    // `left` means the number of elements that are smaller than `target`
    // left tries all positions: from 0 to arr.length
    // the first one (>=) will be at left
#if 1  // if return the first one bigger than (or equal to), don't need this
    if (left == arr.size()) return -1;  // all elements are smaller than target (no lower-bound)
    return (arr[left] == target) ? left : -1;
#else
    return left;
#endif
}

int main()
{
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 5;
        std::cout << "binary search for lower-bound of " << target
            << " at " << lowerBound(arr, target) << "\n";  // lower-bound is 2 for 5
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 4;
        std::cout << "binary search for lower-bound of " << target
            << " at " << lowerBound(arr, target) << "\n";  // lower-bound is -1 for 4
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 8;
        std::cout << "binary search for lower-bound of " << target
            << " at " << lowerBound(arr, target) << "\n";  // lower-bound is 5 for 8
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 9;
        std::cout << "binary search for lower-bound of " << target
            << " at " << lowerBound(arr, target) << "\n";  // lower-bound is -1 for 9
    }
}
