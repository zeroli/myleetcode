#include "utils.h"

/*
You are given an integer array arr, write a program to return the smallest missing positive integer.

Problem Note

    The array is unsorted.
    You need to return the smallest natural number that is not in the list
    You are expected to solve this in O(n) time using O(1) extra space.
*/

// 下面的解法只能适用于数组元素都是正数的情况
// 正负数和0存在的情况下，另外一个解法存在
// refer to array\find-missing-positive-num-negatives-included.cc
int MissingNumber(std::vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++) {
        // swap the number to its exact location, if it's not in this location
        // until it's out of range or at exact location
        // 如果arr[i]为负数，下面的while条件成立
        // 所以它只能适用于正数数组
        while (arr[i] != i + 1 && arr[i] <= arr.size()) {
            std::swap(arr[i], arr[arr[i] - 1]);
        }
    }
    std::cout << arr << "\n";
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != i + 1) {
            return i + 1;
        }
    }
    return arr.size() + 1;
}

int main()
{
    {
        std::vector<int> arr = { 5,1,7,3,9,2,4 };
        std::cout << MissingNumber(arr) << "\n";  // 6
    }
    {
        std::vector<int> arr = { 5,8,3,6,2 };
        std::cout << MissingNumber(arr) << "\n";  // 1
    }
    {
        std::vector<int> arr = { 1,4,3,2 };
        std::cout << MissingNumber(arr) << "\n";  // 5
    }

}
