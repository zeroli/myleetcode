#include "utils.h"

/*
Given an unsorted array of integers arr[] ,
 write a program to find the length of the longest increasing subsequence
 such that all elements of the subsequence are sorted in increasing order.

Problem Note

    The longest subsequence is not necessarily contiguous, or unique.
    There may be more than one LIS combination, it is only necessary for you to return the length.
    Your algorithm should run in O(n^2) complexity. Could you improve it to O(nlogn) time complexity?
*/

int LongestIncreasingSubsequence(const std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> dp(n, 0);
    dp[n-1] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j] > arr[i]) {
                dp[i] = std::max(dp[j] + 1, dp[i]);
            }
        }
    }
    return dp[0];
}

int UpperBound(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (target >= arr[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    // note, we don't return left - 1, usual UpperBound will return index of last one <= target
    // here, we will return real upper limit, first one > target, so no '-1' there
    return left;
}

// runtime will be reduced to O(nlgn)
int LongestIncreasingSubsequencePatientSorting(const std::vector<int>& arr)
{
    // patient sorting with deck card
    /* for example: 3,10,2,1,20
     * 1) iterate through each element
     * (3):   3
     * (10): 3 => 10
     * (2) : 3 => 10
     *        2
     * (1): 3 => 10
     *       2
     *       1
     * (20): 3 => 10 => 20
     *         2
     *         1
     * then finally, 3 piles of cards will be the number (longest), but top ones: 1 => 10 => 20 not answer
     * each element either put on top of pile of cards where its lower bound is there
     * or start a pile, if lower bound is not found, using binary search variant (O(lg(n)))
    */
    std::vector<int> piles;
    for (int i = 0; i < arr.size(); i++) {
        if (piles.empty()) {
            piles.push_back(arr[i]);
        } else {
            // first bigger one, put this one on top of it
            int ipile = UpperBound(piles, arr[i]);
            if (ipile == piles.size()) {
                piles.push_back(arr[i]);
            } else {
                piles[ipile] = arr[i];
            }
        }
    }
    return piles.size();
}

int main()
{
    {
        std::vector<int> arr = { 3,10,2,1,20 };
        std::cout << LongestIncreasingSubsequence(arr) << "\n";  // 3: (3, 10, 20)
        std::cout << LongestIncreasingSubsequencePatientSorting(arr) << "\n";
    }
    {
        std::vector<int> arr = { 0,8,4,2,10,6,1,9,13,3,11,7,15 };
        std::cout << LongestIncreasingSubsequence(arr) << "\n";  // 6
        std::cout << LongestIncreasingSubsequencePatientSorting(arr) << "\n";
        // [0,4,6,9,11,15] or [0,2,6,9,13,15] or [0,4,6,9,13,15]
    }
}
