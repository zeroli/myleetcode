/*
Given an unsorted array arr[] of size n, write a program to find the max (j - i) difference
 between indices such that j > i and arr[j] > arr[i] .
*/

#include "utils.h"

int MaxDiffIndexes(const std::vector<int>& arr)
{
    int maxLen = -1;
    std::pair<int, int> res;
    // build left_min array
    std::vector<int> left_min(arr.size(), 0);
    left_min[0] = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        left_min[i] = std::min(left_min[i-1], arr[i]);
    }
    std::cout << "left min array: " << left_min << "\n";

    int n = arr.size();
    int i = n - 1;
    for (int j = n-1; j >= 0; j--) {
        int cur = arr[j];
        // quickly find the farthest smaller element from current 'j'
        while (i >= 0 && left_min[i] < cur) {
            i--;
        }
        maxLen = std::max(maxLen, j - i - 1);
        //std::cout << "maxlen: " << maxLen << ", " << i << ": " << j << "\n";
    }
    return maxLen;
}

int main()
{
    {
        std::vector<int> arr = { 72, 8, 10, 3, 2, 81, 30, 1, 32 };
        std::cout << MaxDiffIndexes(arr) << "\n";
    }
    {
        std::vector<int> arr = { 5, 2, 3, 5, 4, 6, 7, 8, 19, 0 };
        std::cout << MaxDiffIndexes(arr) << "\n";
    }
    {
        std::vector<int> arr = { 0, 2, 3, 4, 5, 8, 9 };
        std::cout << MaxDiffIndexes(arr) << "\n";
    }
    {
        std::vector<int> arr = { 11, 8, 5, 4, 2, 1 };
        std::cout << MaxDiffIndexes(arr) << "\n";
    }

}
