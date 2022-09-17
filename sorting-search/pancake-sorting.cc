#include "utils.h"

// find index of max value, from 0 to bottom [0, bottom]
int FindMax(const std::vector<int>& arr, int bottom)
{
    int idx = 0;
    int max = arr[0];
    for (int i = 1; i <= bottom; i++) {
        if (max < arr[i]) {
            idx = i;
            max = arr[i];
        }
    }
    return idx;
}

void Reverse(std::vector<int>& arr, int top, int bottom)
{
    while (top < bottom) {
        std::swap(arr[top++], arr[bottom--]);
    }
}

std::vector<int> PancakeSort(std::vector<int>& arr)
{
    int n = arr.size();

    int bottom = n - 1;
    while (bottom >= 1) {
        int max = FindMax(arr, bottom);
        if (max != 0) {
            // reverse [0, max] to make max on top
            Reverse(arr, 0, max);
        }
        // reverse [0, bottom] to make max go to bottom
        Reverse(arr, 0, bottom);
        bottom--;
    }
    return arr;
}

int main()
{
    {
        std::vector<int> arr = { 3, 2, 4, 1};
        std::cout << PancakeSort(arr) << "\n";
    }
}
