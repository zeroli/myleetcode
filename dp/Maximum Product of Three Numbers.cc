#include "utils.h"

/*
Given an integer array arr[],
 write a program to find three numbers in the array whose
  product is maximum and return the maximum product of these three numbers.

Problem Note

    The array contains both +ve and -ve numbers.
    The elements on the array can be non-contiguous.
*/

int MaxProduct(std::vector<int>& arr)
{
    std::sort(arr.begin(), arr.end());
    int n = arr.size();
    // last 3 max elements
    int max1 = arr[n-1] * arr[n-2] * arr[n-3];
    // first 2 negative elements * last max positive element
    int max2 = arr[0] * arr[1] * arr[n-1];
    return std::max(max1, max2);
}

int main()
{
    {
        std::vector<int> arr = { -5, -7, 4, 2, 1, 9 };
        std::cout << MaxProduct(arr) << "\n";  // 315
    }
    {
        std::vector<int> arr = { 4, 5, -19, 3 };
        std::cout << MaxProduct(arr) << "\n";  // 60
    }
}
