#include "utils.h"

// arr is un-sorted array, remove a elements that is equal to `target`
std::vector<int> RemoveElement(std::vector<int>& arr, int target)
{
    int j = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != target) {
            arr[j] = arr[i];
            j++;
        }
    }
    arr.resize(j);
    return arr;
}

int main()
{
    std::vector<int> arr = { 1, 2, 3, 4, 5, 4, 6 };
    std::cout << RemoveElement(arr, 4) << "\n";
}
