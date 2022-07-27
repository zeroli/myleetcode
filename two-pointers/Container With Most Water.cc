#include "utils.h"

int CalculateContainer(const std::vector<int>& arr)
{
    int maxarea = 0;
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        if (arr[left] < arr[right]) {
            maxarea = std::max(maxarea, arr[left] * (right - left));
            left++;
        } else {
            maxarea = std::max(maxarea, arr[right] * (right - left));
            right--;
        }
    }
    return maxarea;
}

int main()
{
    {
        std::vector<int> arr = { 1,8,6,2,5,4,8,3,7 };
        std::cout << CalculateContainer(arr) << "\n";
    }
}
