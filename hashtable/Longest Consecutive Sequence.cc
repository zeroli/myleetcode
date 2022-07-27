#include "utils.h"

/*
Given an unsorted integer array arr consisting of n integers,
 write a program to find the length of the longest consecutive sequence of integers in the array.
*/

int LCS(const std::vector<int>& arr)
{
    std::set<int> numSet;
    for (int i = 0; i < arr.size(); i++) {
        numSet.insert(arr[i]);
    }

    int maxLen = 0;
    int len = 0;
    auto iter = numSet.begin();
    while (iter != numSet.end()) {
        int cur = *iter;
        while (iter != numSet.end() && *iter == (cur + len)) {
            len++;
            ++iter;
        }
        maxLen = std::max(maxLen, len);
        len = 0;
    }
    return maxLen;
}

int main()
{
    {
        std::vector<int> arr = { 1, 9, 3, 10, 4, 20, 2 };
        std::cout << LCS(arr) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 20, 28, 12, 18, 23, 19 };
        std::cout << LCS(arr) << "\n";  // 3
    }
}
