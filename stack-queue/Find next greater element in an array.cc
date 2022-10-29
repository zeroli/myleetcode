#include "utils.h"

/*
Given an array arr of size n, you need to find the next greater element for each element in the array.

Problem Note

    The next greater element is the first greater element on an element’s right side in the array. e.g., an element arr[j] would be the next greater element of arr[i] such that arr[j] > arr[i] , i < j and j - i is minimum.
    Return an array that consists of the next greater element of array arr.
    Elements for which no greater element exist, consider the next greater element as -1.
*/

std::vector<int> NextGreaters(const std::vector<int>& arr)
{
    std::vector<int> ng(arr.size(), -1);

    std::stack<int> stk;  // store index
    for (int i = 0; i < arr.size(); i++) {
        // monotonic descending stack
        // when meet bigger one(current),
        // pop all smaller one until bigger one showup
        while (!stk.empty() && arr[stk.top()] < arr[i]) {
            ng[stk.top()] = arr[i];  // update their next greater
            stk.pop();
        }
        stk.push(i);
    }
    return ng;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        std::cout << NextGreaters(arr) << "\n"; // 2, 3, 4, 5, -1
    }
    {
        std::vector<int> arr = { 12, 1, 0, 17, 10 };
        std::cout << NextGreaters(arr) << "\n"; // 17, 17, 17, -1, -1
    }
}
