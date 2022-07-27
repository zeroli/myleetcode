/*
Given an array nums which consists of non-negative integers and an integer m,
 you can split the array into m non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these m subarrays.

Example 1:

Input: nums = [7,2,5,10,8], m = 2
Output: 18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.

Example 2:

Input: nums = [1,2,3,4,5], m = 2
Output: 9

Example 3:

Input: nums = [1,4,4], m = 3
Output: 4

*/

#include "utils.h"

struct Key {
    int s, e;  // subarray
    int k;  // how many cut left

    friend bool operator <(const Key& k1, const Key& k2)
    {
        if (k1.s != k2.s) return k1.s < k2.s;
        if (k1.e != k2.e) return k1.e < k2.e;
        return k1.k < k2.k;
    }
};

// key => larget sum
using Memo_t = std::map<Key, int>;

void backtracking(const std::vector<int>& arr, int startIdx, int K,
    int pathLargetSum, int& minSum, Memo_t& memo)
{
    int n = arr.size();
    if (memo.find({startIdx, n, K}) != memo.end()) {
        return;
    }

    if (K == 0) {
        // we need consider the remaining subarray
        int sum = std::accumulate(&arr[startIdx], &arr[arr.size()], 0);
        pathLargetSum = std::max(pathLargetSum, sum);

        minSum = std::min(pathLargetSum, minSum);
        std::cout << "minSum: " << minSum << "\n";
        return;
    }

    for (int i = startIdx; i < arr.size(); i++) {
        // subarray: [startIdx, i]
        int sum = std::accumulate(&arr[startIdx], &arr[i+1], 0);
        std::cout << "subarray: [" << startIdx << "," << i << "]: " << sum << "\n";
        backtracking(arr, i + 1, K - 1, std::max(pathLargetSum, sum), minSum, memo);
        auto& largetSum = memo[{startIdx, n, K}];
        largetSum = std::max(largetSum, memo[{i+1, n, K-1}]);
    }
}

int MinLargetSum(const std::vector<int>& arr, int m)
{
    Memo_t memo;
    int largestSum = 0;
    int minSum = INT_MAX;
    backtracking(arr, 0, m - 1, largestSum, minSum, memo);
    return minSum;
}

int main()
{
    {
        std::vector<int> arr = { 7,2,5,10,8 };
        int m = 2;
        std::cout << MinLargetSum(arr, m) << "\n";  // 18
    }
    {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        int m = 2;
        std::cout << MinLargetSum(arr, m) << "\n";  // 9
    }
    {
        std::vector<int> arr = { 1, 4, 4 };
        int m = 3;
        std::cout << MinLargetSum(arr, m) << "\n";  // 4
    }
}
