#include "utils.h"

int TargetAtIndexNoDup(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] > arr[right]) {  // left part is ascending order
            if (target >= arr[left] && target < arr[mid]) {  // target in this left part
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {  // right part is ascending order
            if (target > arr[mid] && target <= arr[right]) {  // target in this right part
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int main()
{
    {
        std::vector<int> arr = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
        int k = 3;
        std::cout << TargetAtIndexNoDup(arr, k) << "\n";
    }
}
