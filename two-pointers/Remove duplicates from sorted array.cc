/*
Remove duplicates from sorted array

You are given an array arr[] of size n with duplicate elements, write a program to remove all duplicates from the array, and return the size of the new array.

Problem Notes

    All elements of the resultant array must be unique.
    It's better if the algorithm is in-place.
*/
#include "utils.h"

int RemoveDuplicates(std::vector<int>& arr)
{
    int j = 0;  // 每个unique元素
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != arr[j]) {
            arr[++j] = arr[i];
        }
    }
    arr.resize(j + 1);
    return j + 1;
}

int main()
{
    {
        std::vector<int> arr = { -1, 0, 1, 1, 2, 9, 9 };
        std::cout << RemoveDuplicates(arr) << "->";  // 5
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { -10, 1, 3, 6, 6, 6, 6, 10 };
        std::cout << RemoveDuplicates(arr) << "->";  // 5
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { 10, 20, 30, 33, 45 };
        std::cout << RemoveDuplicates(arr) << "->";  // 5
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { 1, 1, 1, 1, 1, 1 };
        std::cout << RemoveDuplicates(arr) << "->";  // 1
        std::cout << arr << "\n";
    }
}
