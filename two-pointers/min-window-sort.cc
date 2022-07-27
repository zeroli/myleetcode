#include "utils.h"

// Given an array, find the length of the smallest subarray in it
// which when sorted will sort the whole array.

int lowerBound(const std::vector<int>& arr, int left, int right, int target)
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

int upperBound(const std::vector<int>& arr, int left, int right, int target)
{
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (target >= arr[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left - 1;
}

std::pair<int, int> MinWindowSort(const std::vector<int>& arr)
{
    int i = 0, j = arr.size() - 1;
    int left = 0, right = 0;

    // find the first element smaller than previous one (from begin to search)
    while (i + 1 < arr.size() && arr[i] <= arr[i+1]) {
        i++;
    }
    left = i;
    // find the first element bigger than previous one (from end to search)
    while (j > 0 && arr[j] >= arr[j-1]) {
        j--;
    }
    right = j;
    std::cout << "left: " << left << ", right: " << right << "\n";

    if (left >= right) {  // no need sort, all sorted
        return { -1,  -1 };
    }

    // extend left and right
    int s = left, e = right;  // including
#if 1
    int min = INT_MAX, max = INT_MIN;
    for (int i = left; i <= right; i++) {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
    }
    while (s - 1 >= 0 && arr[s-1] > min)
        s--;
    while (e + 1 < (int)arr.size() - 1 && arr[e+1] < max)
        e++;
#else
    for (int i = left + 1; i < right; i++) {
        // use upper bound to handle duplicated ones
        int index = upperBound(arr, 0, left + 1, arr[i]);
        if (index < left) {  // should go to left, otherwise, all are smaller
            s = std::min(s, index + 1);
        } else {  // check if should go to right
            // use lower bound to handle duplicated ones
            index = lowerBound(arr, right, arr.size(), arr[i]);
            if (index == arr.size()) {  // all are smaller
                e = arr.size() - 1;
            } else {  //
                e = std::max(e, index - 1);
            }
        }
    }
#endif
    return { s, e };
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 5, 3, 7, 10, 9, 12 };
        std::cout << MinWindowSort(arr) << "\n";
    }
    {
        std::vector<int> arr = {1, 3, 2, 0, -1, 7, 10};
        std::cout << MinWindowSort(arr) << "\n";
    }
    {
        std::vector<int> arr = { 1, 2, 3 };
        std::cout << MinWindowSort(arr) << "\n";
    }
    {
        std::vector<int> arr = { 3, 2, 1 };
        std::cout << MinWindowSort(arr) << "\n";
    }
}
