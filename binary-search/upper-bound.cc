#include "utils.h"

// return upper-bound (the last <= target) of target in array
// return -1 if cannot find it
int upperBound(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (target >= arr[mid]) {
            left = mid + 1;
        } else {  // target < arr[mid]
            right = mid;
        }
    }
    // `left` searches for [0, arr.size()]
    // left means how many elements are smaller than (or equal to target)
    // so the last one (<=) will be at left - 1
    // if left=0, it means no elements <= target, all elements are bigger than it
#if 1  // if return the index where last element smaller than (or equal to) target, don't need this
    if (left == 0) return -1;
    return arr[left - 1] == target ? (left - 1) : -1;
#else
    return left - 1;
#endif
}

int main()
{
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 0;
        std::cout << "binary search for upper-bound of " << target
            << " at " << upperBound(arr, target) << "\n";  // upper-bound is -1 for 0
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 5;
        std::cout << "binary search for upper-bound of " << target
            << " at " << upperBound(arr, target) << "\n";  // upper-bound is 2 for 5
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 4;
        std::cout << "binary search for upper-bound of " << target
            << " at " << upperBound(arr, target) << "\n";  // upper-bound is -1 for 4
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 8;
        std::cout << "binary search for upper-bound of " << target
            << " at " << upperBound(arr, target) << "\n";  // upper-bound is 6 for 8
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 9;
        std::cout << "binary search for upper-bound of " << target
            << " at " << upperBound(arr, target) << "\n";  // upper-bound is -1 for 9
    }
}
