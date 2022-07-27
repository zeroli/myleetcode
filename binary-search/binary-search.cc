#include "utils.h"

// return location of target value in array
// return -1 if cannot find it
int binarySearch(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int main()
{
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 5;
        std::cout << "binary search " << target << " at " << binarySearch(arr, target) << "\n";
    }
    {
        std::vector<int> arr = { 1, 3, 5, 6, 7, 8, 8 };
        int target = 4;
        std::cout << "binary search " << target << " at " << binarySearch(arr, target) << "\n";
    }
}
