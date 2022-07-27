#include "utils.h"

/*
Given an array of non-negative integers arr[] of length n,
 where each element represents the max number of steps that can be made forward from that element.
 You are initially positioned at the first index of the array.
 Write a program to return the minimum number of jumps to reach the last index of the array.

Problem Note

    If it is not possible to reach the last index, return -1.
    If an element is 0, then you cannot move through that element.
*/

int MinJumps(const std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> dp(n, INT_MAX);
    dp[n-1] = 0;  // last position going to last position will take 0 step
    for (int i = n - 1; i >= 0; i--) {
        // for this location, take 1, up to arr[i] steps to next position, try them
        // to see which one has minimum steps
        for (int j = 1; j <= arr[i]; j++) {
            if (i + j < n) {
                dp[i] = std::min(dp[i], dp[i + j] + 1);
                std::cout << i << ", " << j << ":" << dp << "\n";
            }
        }
    }
    return dp[0] == INT_MAX ? -1 : dp[0];
}

int main()
{
    {
        std::vector<int> arr = { 2, 1, 1 };
        std::cout << MinJumps(arr) << "\n";  // 1
    }
    {
        std::vector<int> arr = { 2, 3, 2, 4, 4 };
        std::cout << MinJumps(arr) << "\n";  // 2
    }
}
