#include "utils.h"

/*
Given an array of integers arr[] and a target number k,
write a program to find all unique combinations in arr[]
such that the sum of all integers in the combination is equal to k.

Problem Note

    All numbers (including target number k) will be positive integers.
    The same number may be chosen from arr[] unlimited number of times.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (i.e, a1 ≤ a2 ≤ … ≤ ak).
    The combinations themselves must be sorted in ascending order, i.e., the combination with the smallest first element should be printed first.
    The solution set must not contain duplicate combinations.
*/

using Path_t = std::vector<int>;

void BackTracking(const std::vector<int>& arr, int startIndex, int targetSum, int sum,
    Path_t& path, std::vector<Path_t>& results)
{
    if (sum > targetSum) {
        return;
    }
    if (sum == targetSum) {
        results.push_back(path);
        return;
    }

    for (int i = startIndex; i < arr.size(); i++) {
        path.push_back(arr[i]);
        sum += arr[i];
        // still i (instead of i + 1, since we could choose this one unlimited times)
        BackTracking(arr, i, targetSum, sum, path, results);
        path.pop_back();
        sum -= arr[i];
    }
}

std::vector<Path_t> CombinationSum(std::vector<int>& arr, int targetSum)
{
    std::sort(arr.begin(), arr.end());

    Path_t path;
    std::vector<Path_t> results;
    BackTracking(arr, 0, targetSum, 0, path, results);
    return results;
}

int main()
{
    {
        std::vector<int> arr = { 2,4, 6, 8 };
        int k = 8;
        std::cout << CombinationSum(arr, k) << "\n";
    }
}
