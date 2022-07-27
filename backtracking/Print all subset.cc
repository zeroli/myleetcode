#include "utils.h"

/*
Given a set of distinct integers S, return all possible subsets.

Problem Note

    The solution set must not contain duplicate subsets.
    The set is not necessarily sorted.
    You can return all subsets in any order(not necessarily sorted).
    The total number of subsets of a given set of size n is equal to 2^n.
*/

using Path_t = std::vector<int>;

void BackTracking(const std::vector<int>& arr, int startIndex,
    Path_t& path, std::vector<Path_t>& results)
{
    results.push_back(path);

    for (int i = startIndex; i < arr.size(); i++) {
        path.push_back(arr[i]);
        BackTracking(arr, i + 1, path, results);
        path.pop_back();
    }
}

std::vector<Path_t> AllSubsets(const std::vector<int>& arr)
{
    Path_t path;
    std::vector<Path_t> results;
    BackTracking(arr, 0, path, results);
    return results;
}

int main()
{
    {
        std::vector<int> arr = { 2,3,4 };
        std::cout << AllSubsets(arr) << "\n";
    }
}
