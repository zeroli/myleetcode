/*
Given an array arr[] of n elements filled with several integers, some of them being zeroes, write a program to move all the zeroes to the end.

Problem Note

    The relative order of non-zero integers needs to remain the same as in the original array.
    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/

#include "utils.h"

std::vector<int>& MoveZeroToEnd(std::vector<int>& arr)
{
    int slow = 0;
    for (int fast = 0; fast < arr.size(); fast++) {
        if (arr[fast] != 0) {
            std::swap(arr[slow], arr[fast]);
            slow++;
        }
    }
    return arr;
}

int main()
{
    {
        std::vector<int> arr = { 1, 8, 0, 2, 0, 1, 13, 0 };
        std::cout << "input: " << arr << "\n"
            "output: " << MoveZeroToEnd(arr) << "\n";
    }
    {
        std::vector<int> arr = { 0, 0, 0, 23, 2 };
        std::cout << "input: " << arr << "\n"
            "output: " << MoveZeroToEnd(arr) << "\n";
    }
}
