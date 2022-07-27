#include "utils.h"

int SearchTarget(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (target == arr[mid]) {
            return mid;
        }

        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;  // no one is equal to target
            right--;
        } else if (arr[left] == arr[mid]) {
            left = mid + 1;  // remove half of it, since [left... mid-1] not equal to target
        } else if (arr[right] == arr[mid]) {
            right = mid - 1;  // remove half of it, since [mid+1... right] not equal to target
        } else if (arr[mid] < arr[right]) {  // right part is ascending order
            if (arr[mid] < target && target <= arr[right]) {  // in range
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {  // left part is ascending order
            if (arr[left] <= target && target < arr[mid]) {  // in range
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return -1;
}

int main()
{
    {
        std::vector<int> arr = { 2,5,6,0,0,1,2 };
        int target = 0;
        std::cout << SearchTarget(arr, target) << "\n";
    }
    {
        std::vector<int> arr = { 2,5,6,0,0,1,2 };
        int target = 3;
        std::cout << SearchTarget(arr, target) << "\n";
    }
}
